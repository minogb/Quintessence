// Fill out your copyright notice in the Description page of Project Settings.

#include "Avatar.h"
#include "Components/CapsuleComponent.h"
#include "AvatarController.h"
#include "Engine/GameEngine.h"
#include "TimerManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/ArrowComponent.h"
#include "UnrealNetwork.h"
#include "Item_World.h"
#include "Item.h"
#include  "QuintPlayerController.h"
#include "ResourceNode.h"
#include "Tool.h"
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
	SetReplicates(true);
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
			if(!IsValid(GoalActor)){
				Stop();
			}
			else if(!IsDoingTask && !IsTaskOnCoolDown){
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
	if(IsDoingTask){
		PercentTaskCompleted = GetWorldTimerManager().GetTimerElapsed(TaskTimer) / GetCurrentTaskDuration();
	}
}

void AAvatar::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );
	DOREPLIFETIME(AAvatar, Health);
	DOREPLIFETIME(AAvatar, PercentTaskCompleted);
	DOREPLIFETIME(AAvatar, IsDoingTask);
	DOREPLIFETIME(AAvatar, TurnSpeed);
	DOREPLIFETIME(AAvatar, IsInCombat);
	
}
// Called to bind functionality to input
void AAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent){
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AAvatar::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	if(!HasAuthority())
		return 0.f;
	SetIsInCombat(true);
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
	IInteractable* goal = Cast<IInteractable>(GoalActor);
	float bonusDistance = IsValid((UObject*)goal) ? goal->GetSize() : 0;
	switch(GoalAction){
	case Attack:
		//Calculate based on weapon
		return bonusDistance + 80.f;
	default:
		return bonusDistance + 80.f;
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

void AAvatar::StartDoingTask() {
	if (!HasAuthority())
		return;
	if (!CanDoCurrentTask()) {
		Stop();
		return;
	}
	IsDoingTask = true;
	AAvatarController* controller = Cast<AAvatarController>(GetController());
	if (controller) {
		controller->StopMovement();
	}
	if (IsTaskCombatTask())
		SetIsInCombat();
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
	GetWorldTimerManager().ClearTimer(TaskTimer);
	AAvatarController* controller = Cast<AAvatarController>(GetController());
	if(controller){
		controller->StopMovement();
	}
}

float AAvatar::GetCurrentTaskDuration(){
	switch(GoalAction){
	case Attack:
		//Calculate based on weapon
		return .5;
		break;
	case Harvest:
		//Calculate base on node
		return 1.f;
	default:
		return 0.1;
		break;
	}
}

float AAvatar::GetCurrentTaskCoolDownDuration(){
	switch(GoalAction){
	case Attack:
		//Calculate based on weapon
		return 1.f;
	case Harvest:
		return .4;
	default:
		return 0.5;
	}
}

AQuintPlayerController * AAvatar::GetQuintController()
{
	return Cast<AQuintPlayerController>(GetOwner());
}

void AAvatar::TaskCompleted(){
	GetWorldTimerManager().ClearTimer(TaskTimer);
	if(!HasAuthority())
		return;
	
	if(!IsValid(GoalActor) || !GoalActor){
		Stop();
	}
	//Once we are done we are no longer working on the task
	IsDoingTask = false;
	//Every task has a cool down period to prevent future tasks
	IsTaskOnCoolDown = true;
	//Set how long we are on cool down for
	if(GetWorld())
		GetWorldTimerManager().SetTimer(TaskCoolDownTimer,this, &AAvatar::EndTaskCooldown,GetCurrentTaskCoolDownDuration(),false);
	
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
	case Pick_Up:
		PickUpTask();
		Stop();
		break;
	case Harvest:
		HarvestTask();
		break;
	default:
		Stop();
		break;
	}
	if(GEngine)
      GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Task Completed")); 
}

void AAvatar::EndTaskCooldown(){
	if(!HasAuthority())
		return;
	IsTaskOnCoolDown = false;
}

void AAvatar::PickUpTask(){
	if(!HasAuthority())
		return;
		AItem_World* goal = Cast<AItem_World>(GoalActor);
		if(!IsValid(goal)){
			Stop();
		}
		else{
			AQuintPlayerController* owner = Cast<AQuintPlayerController>(GetOwner());
			if(owner){
				owner->AddItemToInventory(goal);
			}
		}
}

void AAvatar::HarvestTask(){
	//TODO GET REWAREDS
	AResourceNode* node = Cast<AResourceNode>(GoalActor);
	if(IsValid(node)){
		node->HarvestThis(this);
	}
}

void AAvatar::SetIsInCombat(bool Combat){
	if(!HasAuthority())
		return;
	IsInCombat = Combat;
	if(IsInCombat && GetWorld())
		GetWorldTimerManager().SetTimer(IsInCombatTimer,this, &AAvatar::EndOfCombat,CombatTimeOutSpeed,false);
}

void AAvatar::EndOfCombat(){
	SetIsInCombat(false);
}

bool AAvatar::IsTaskCombatTask(){
	return GoalAction == Attack;
}

bool AAvatar::ValidTask(){
	return ValidGoal() || !GoalLocation.Equals(INVALID_LOCATION);
}

bool AAvatar::CanDoCurrentTask(){
	IInteractable* task =  Cast<IInteractable>(GoalActor);
	return IsValid((UObject*)task) ? task->IsValidTask(GoalAction,this) : true;
}

int AAvatar::GetHighestToolLevelOfType(EHarvestType Type)
{
	//Search Inventory

	AQuintPlayerController* controller = GetQuintController();
	if(IsValid(controller))
		return controller->GetHighestToolLevelOfType(Type);
	//TODO: check equiped weapon
	return 0;
}

void AAvatar::ReplicateDamageRecived_Implementation(int Amount){
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *FString::FromInt(Amount)); 
}
