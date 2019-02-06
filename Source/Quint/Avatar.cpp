// Fill out your copyright notice in the Description page of Project Settings.

#include "Avatar.h"
#include "Components/CapsuleComponent.h"
#include "AvatarController.h"
#include "Engine/GameEngine.h"
#include "TimerManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/ArrowComponent.h"
#include "UnrealNetwork.h"

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
		FVector Direction = ((ValidGoal() ? GoalActor->GetActorLocation() : GoalLocation) - GetActorLocation());
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
			else if (IsDoingTask){
				PercentTaskCompleted = GetWorldTimerManager().GetTimerElapsed(TaskTimer) / GetCurrentTaskDuration();
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

void AAvatar::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );
	DOREPLIFETIME(AAvatar, Health);
	DOREPLIFETIME(AAvatar, PercentTaskCompleted);
	DOREPLIFETIME(AAvatar, IsDoingTask);
	
}
// Called to bind functionality to input
void AAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent){
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AAvatar::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	if(!HasAuthority())
		return 0.f;
	DamageEvent.ClassID;
	DamageEvent.DamageTypeClass;
	int FinalHealthRemoved = (Health-DamageAmount) >= 0.f ? DamageAmount : Health;
	Health -= FinalHealthRemoved;
	if(Health<= 0.f){ 
		Destroy(true);
	}
	return FinalHealthRemoved;
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
		return 80.f;
	default:
		return 80.f;
	}
}

bool AAvatar::IsAtGoal(){
	if(ValidGoal()){
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
		if(ValidGoal()){
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
		break;
	case Follow:
		return 0.5;
		break;
	default:
		return 0.1;
		break;
	}
}

float AAvatar::GetCurrentTaskCoolDownDuration(){
	switch(GoalAction){
	case Attack:
		if(GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("attack task cd")); 
		//Calculate based on weapon
		return 0.1;
	case Follow:
		if(GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("follow task cd")); 
		return 0.5;
	default:
		if(GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Default task cd")); 
		return 0.1;
	}
}

void AAvatar::TaskCompleted(){
	TaskTimer.Invalidate();
	if(!HasAuthority())
		return;

	//Once we are done we are no longer working on the task
	IsDoingTask = false;
	//Every task has a cool down period to prevent future tasks
	IsTaskOnCoolDown = true;
	
	switch(GoalAction){
	case Attack:
		//Attack
		if(ValidGoal()){
			FDamageEvent dmgEvent = FDamageEvent();
			GoalActor->TakeDamage(5.f,dmgEvent,GetController(),this);
			if(GEngine)
			  GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Damage Delt")); 
		}
		else{
			Stop();
		}
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
	return (ValidGoal() && GoalAction != No_Interaction) || !GoalLocation.Equals(INVALID_LOCATION);
}

void AAvatar::ReplicateDamageRecived_Implementation(int Amount){
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *FString::FromInt(Amount)); 
}
