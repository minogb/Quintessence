// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "QuintPlayerController.h"
#include "AI/Navigation/NavigationSystem.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "QuintCharacter.h"
#include "Engine/World.h"
#include "Engine.h"
#include "QuintPlayerState.h"
#include "InteractableInterface.h"
#include "WeaponHelper.h"

AQuintCharacter * AQuintPlayerController::GetPlayerPawn()
{
	return Cast<AQuintCharacter>(GetPawn());
}


AQuintPlayerController::AQuintPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void AQuintPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (HasAuthority()) {
		if (Goal) {
			if (IsAtGoal() && !DoingTask && IsTaskReadyIfUsed()) {
				DoTask();
			}
			else if(!DoingTask) {
				MoveToGoal();
			}
		}
		else {
		}
		//TODO: Load equipment
		GetPlayerState()->SetPlayerPrimary(0);
	}
}

void AQuintPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AQuintPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AQuintPlayerController::OnSetDestinationReleased);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AQuintPlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AQuintPlayerController::MoveToTouchLocation);

}

void AQuintPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	APawn* const MyPawn = GetPawn();
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);

	if (HitResult.bBlockingHit && MyPawn) {
		float const Distance = FVector::Dist(HitResult.ImpactPoint, MyPawn->GetActorLocation());
		//Should we bother with the network call
		if (Distance > GetMinRange())
			// We hit something, move there
			SetNewMoveDestination(HitResult.ImpactPoint, HitResult.Actor.Get());
	}
}

void AQuintPlayerController::SetNewMoveDestination_Implementation(const FVector DestLocation, AActor* DestActor){
	IInteractableInterface* InteractableObject = Cast<IInteractableInterface>(DestActor);
	if (InteractableObject) {
		SetTask(DestActor, InteractableObject->GetDefaultTask());
	}
	else {
		StopDoingTask();
		MoveToLocation(DestLocation);
	}
}
void AQuintPlayerController::SetTask(AActor* goal, EInteractionType task){
	if(task == Task && goal == Goal)
		return;
	StopDoingTask();
	if (!goal || task == No_Interaction || goal == GetPawn()) {
		Goal = nullptr;
		task = No_Interaction;
		return;
	}
	Goal = goal;
	Task = task;
	switch (task)
	{
	case Move_Here:
		if (Goal) {
			MaxGoalDistance = GetMinRange();
			MoveToLocation(Goal->GetActorLocation());
			DoingTask = true;
		}
		break;
	case Examine:
		MaxGoalDistance = GetMinRange();
		break;
	case Use:
		MaxGoalDistance = GetMinRange();
		MoveToGoal();
		break;
	default:
		MoveToGoal();
		break;
	}
}

void AQuintPlayerController::MoveToGoal()
{
	if (!IsAtGoal()) {
		UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
		NavSys->SimpleMoveToActor(this, Goal);
	}
	
}

void AQuintPlayerController::MoveToLocation(FVector location){
	APawn* const MyPawn = GetPawn();
	float const Distance = FVector::Dist(location, MyPawn->GetActorLocation());
	UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();

	// We need to issue move command only if far enough in order for walk animation to play correctly
	if (NavSys && (Distance > GetMinRange()))	{
		StopDoingTask();
		NavSys->SimpleMoveToLocation(this, location);
	}
}

bool AQuintPlayerController::IsAtGoal(){
	if (!Goal)
		return false;
	float const Distance = FVector::Dist(Goal->GetActorLocation(), GetPawn()->GetActorLocation());
	return Distance <= GetMaxRangeDistance();
}

bool AQuintPlayerController::IsTaskReadyIfUsed()
{
	
	switch (Task)
	{
	case Attack:
		return TaskCoolDownTimer.IsValid();
	default:
		return true;
	}
}

void AQuintPlayerController::SetTaskCoolDownTime(float time)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Set cd");
	UWorld* world = GetWorld();
	if(world)
		world->GetTimerManager().SetTimer(TaskCoolDownTimer, this, &AQuintPlayerController::TaskCoolDownDone, time, false);
}

void AQuintPlayerController::DoTask()
{
	if (!GetPlayerPawn() || !Goal || !HasAuthority() || Task == No_Interaction) {
		return;
	}
	IInteractableInterface* goal = Cast<IInteractableInterface>(Goal);
	//TODO: Face twoard target
	GetPlayerPawn()->FaceRotation(FRotator());
	switch (Task)
	{
	case Move_Here:
		StopDoingTask();
		break;
	case Examine:
		StopDoingTask();

		break;
	case Attack:
		DoingTask = true;
		GetPlayerPawn()->ReplicatePrimaryAttackAnimation();
		break;

	case Follow:
		DoingTask = false;
		break;

	case Use:
		if (goal)
			goal->UseObject();
		StopDoingTask();
		break;

	default:
		StopDoingTask();
		break;
	}
}

void AQuintPlayerController::StopDoingTask()
{
	Goal = nullptr;
	Task = No_Interaction;
	DoingTask = false;
}

void AQuintPlayerController::OnSetDestinationPressed()
{
}

void AQuintPlayerController::OnSetDestinationReleased()
{
	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit) {
		float const Distance = FVector::Dist(Hit.Location, GetPawn()->GetActorLocation());
		// We hit something, move there
		if (Hit.Actor.Get() || Distance > GetMinRange())
			SetNewMoveDestination(Hit.ImpactPoint, Hit.Actor.Get());
	}
}

void AQuintPlayerController::ActionAnimDone()
{
	if(!HasAuthority())
		return;

	FWeaponDataStruct wpStruct; 
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Done action anim");   
	switch (Task)
	{
	case Attack:
		DoingTask = false;
		//TODO:GET primary weapon
		if(UWeaponHelper::GetWeaponOrDefault(0,wpStruct))
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::FromInt((int)wpStruct.WeaponSpeed));  
		SetTaskCoolDownTime(wpStruct.WeaponSpeed);
		//either spawn projectile or apply damage*/ 
		break;
	default:
		break;
	}
}
bool AQuintPlayerController::SetNewMoveDestination_Validate(const FVector DestLocation, AActor* DestActor) { return true; }