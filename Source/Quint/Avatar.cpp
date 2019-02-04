// Fill out your copyright notice in the Description page of Project Settings.

#include "Avatar.h"
#include "Components/CapsuleComponent.h"
#include "AvatarController.h"
#include "Engine/GameEngine.h"
#include "TimerManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/ArrowComponent.h"

// Sets default values
AAvatar::AAvatar(){
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->bHiddenInGame = false;
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Interactable,ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn,ECR_Ignore);
	AIControllerClass= AAvatarController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	GetCharacterMovement()->RotationRate = FRotator(TurnSpeed);
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationPitch = false;
	GetArrowComponent()->SetVisibility(true);
	GetArrowComponent()->bHiddenInGame = false;
}

// Called when the game starts or when spawned
void AAvatar::BeginPlay(){
	Super::BeginPlay();
	
}

// Called every frame
void AAvatar::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
	if(!HasAuthority())
		return;
	if(ValidTask()){
		
		//if !facing target face it
		FVector Direction = ((GoalActor ? GoalActor->GetActorLocation() : GoalLocation) - GetActorLocation());
		Direction.Normalize();
		float diffInYaw = Direction.Rotation().Yaw - GetActorRotation().Yaw;
		if(diffInYaw > 3 || diffInYaw < -3){
			diffInYaw = FMath::Clamp(diffInYaw,TurnSpeed*-1,TurnSpeed);
			FRotator rotator = FRotator(0.f,diffInYaw,0.f);
			AddActorWorldRotation(rotator);
		}
		//At goal
		else if(IsAtGoal()){
			//Can do task
			if(!IsDoingTask && !IsTaskOnCoolDown){
				StartDoingTask();
			}
			//if can't do task, do nothing
		}
		//Am I not doing anything? and am I 
		else{
			//Am I not at goal and doing a task?
			if(IsDoingTask){
				//stop doing task out of range
				InteruptTask();
			}
			//If I am not at goal move to goal
			MoveToLocationOrGoal();
		}
	}

}

// Called to bind functionality to input
void AAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent){
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void AAvatar::SetLocationGoal(FVector Location){
	if(!HasAuthority())
		return;
	if(HasAuthority()){
		Stop();
		GoalLocation = Location;
	}
}

void AAvatar::SetGoalAndAction(AActor * Goal, EInteractionType Action){ 
	if(!HasAuthority())
		return;
	Stop();
	GoalActor = Goal;
	GoalAction = Action;
}

float AAvatar::GetGoalDistance(){
	switch(GoalAction){
	case Attack:
		//Calculate based on weapon
		return 0.f;
	default:
		return 180.f;
	}
}

bool AAvatar::IsAtGoal(){
	if(GoalActor){
		return this->GetActorLocation().Equals(GoalActor->GetActorLocation(),GetGoalDistance());
	}
	else{
		//If invalid location we are always at goal, otherwise use calculated distance
		return GoalLocation.Equals(INVALID_LOCATION) || this->GetActorLocation().Equals(GoalLocation,GetGoalDistance());
	}
}

void AAvatar::MoveToLocationOrGoal(){
	if(!HasAuthority())
		return;
	AAvatarController* controller = Cast<AAvatarController>(GetController());
	if(controller){
		if(GoalActor){
			controller->MoveToActor(GoalActor);
		}
		else{
			controller->MoveToLocation(GoalLocation);
		}
	}
}

void AAvatar::StartDoingTask(){
	if(!HasAuthority())
		return;
	IsDoingTask = true;
	if(GetWorld())
		GetWorldTimerManager().SetTimer(TaskTimer,this, &AAvatar::TaskCompleted,GetCurrentTaskDuration(),false);
}

void AAvatar::Stop(){
	if(!HasAuthority())
		return;
	InteruptTask();
	GoalActor = nullptr;
	GoalAction = No_Interaction;
	GoalLocation = INVALID_LOCATION;
}

void AAvatar::InteruptTask(){
	if(!HasAuthority())
		return;
	IsDoingTask= false;
	AAvatarController* controller = Cast<AAvatarController>(GetController());
	if(controller){
		controller->StopMovement();
		GetWorldTimerManager().ClearTimer(TaskTimer);
	}
}

float AAvatar::GetCurrentTaskDuration(){
	switch(GoalAction){
	case Attack:
		//Calculate based on weapon
		return 2.f;
	case Follow:
		0.5;
	default:
		return 1.f;
	}
}

float AAvatar::GetCurrentTaskCoolDownDuration(){
	switch(GoalAction){
	case Attack:
		//Calculate based on weapon
		return 2.f;
	case Follow:
		return 0.5;
	default:
		return 1.f;
	}
}

void AAvatar::TaskCompleted(){
	if(!HasAuthority())
		return;
	//Once we are done we are no longer working on the task
	IsDoingTask = false;
	//Every task has a cool down period to prevent future tasks
	IsTaskOnCoolDown = true;
	
	switch(GoalAction){
	case Attack:
		//Attack
		break;
	case Follow:
		break;
	default:
		Stop();
		break;
	}
	if(GEngine)
      GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Task Completed")); 
	//Set how long we are on cool down for
	if(GetWorld())
		GetWorldTimerManager().SetTimer(TaskTimer,this, &AAvatar::EndTaskCooldown,GetCurrentTaskCoolDownDuration(),false);
}

void AAvatar::EndTaskCooldown(){
	if(!HasAuthority())
		return;
	IsTaskOnCoolDown = false;
}

bool AAvatar::ValidTask(){
	return (GoalActor && GoalAction != No_Interaction) || !GoalLocation.Equals(INVALID_LOCATION);
}
