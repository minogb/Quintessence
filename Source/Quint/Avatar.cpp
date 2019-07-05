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
#include "Interfaces/Tool.h"
#include "CraftingInfo.h"
#include "Kismet/KismetMathLibrary.h"

/*
-------------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------PRIVATE---------------------------------------------------------------------------------
--------------------------------------------------FUNCTIONS--------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------
*/

// Called when the game starts or when spawned
void AAvatar::BeginPlay() {
	Super::BeginPlay();
}

//--------------------------------------------------------
//---------------------------GOAL-------------------------
//--------------------------------------------------------

//--------------------------------------------------------
//-------------------GET GOAL DISTANCE--------------------
float AAvatar::GetGoalDistance() {

	float bonusDistance = 0;
	if (IsValid(GoalActor) && GoalActor->GetClass()->ImplementsInterface(UInteractable::StaticClass())) {

		bonusDistance = IInteractable::Execute_GetSize(GoalActor);
	}
	switch (GoalAction) {
	case EInteractionType::Attack:
		//Calculate based on weapon
		return bonusDistance + 80.f;
	default:
		return bonusDistance + 80.f;
	}
}

//--------------------------------------------------------
//----------------------IS AT GOAL------------------------
bool AAvatar::IsAtGoal() {
	if (ValidGoal()) {
		return this->GetActorLocation().Equals(GoalActor->GetActorLocation(), GetGoalDistance());
	}
	else {
		//If invalid location we are always at goal, otherwise use calculated distance
		return GoalLocation.Equals(INVALID_LOCATION) || this->GetActorLocation().Equals(GoalLocation, GetGoalDistance());
	}
}

//--------------------------------------------------------
//---------------MOVE TO LOCATION OR GOAL-----------------
void AAvatar::MoveToLocationOrGoal() {
	if (!HasAuthority())
		return;
	AAvatarController* controller = Cast<AAvatarController>(GetController());
	if (controller) {
		if (ValidGoal()) {
			//Note: Pathfinding turned of for move to actor as it seems a bit buggy
			switch (controller->MoveToActor(GoalActor, GetGoalDistance() / 2,false,false,true,0,true)) {
			case EPathFollowingRequestResult::Type::RequestSuccessful:
				break;
			case EPathFollowingRequestResult::Type::AlreadyAtGoal:
				break;
			case EPathFollowingRequestResult::Type::Failed:
				break;
			}
		}
		else {
			controller->MoveToLocation(GoalLocation);
		}
	}
}

//--------------------------------------------------------
//------------------START DOING TASK----------------------
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
	if (GetWorld())
		GetWorldTimerManager().SetTimer(TaskTimer, this, &AAvatar::TaskCompleted, GetCurrentTaskDuration(), false);
}

//--------------------------------------------------------
//-------------------------STOP---------------------------
void AAvatar::Stop() {
	if (!HasAuthority())
		return;
	InteruptTask();
	GoalActor = nullptr;
	GoalAction = EInteractionType::No_Interaction;
	GoalLocation = INVALID_LOCATION;
	UseObject = nullptr;
}

//--------------------------------------------------------
//-------------------INTERUPT TASK------------------------
void AAvatar::InteruptTask() {
	if (!HasAuthority())
		return;
	IsDoingTask = false;
	GetWorldTimerManager().ClearTimer(TaskTimer);
	AAvatarController* controller = Cast<AAvatarController>(GetController());
	if (controller) {
		controller->StopMovement();
	}
}

//--------------------------------------------------------
//-------------------TASK COMPLETED-----------------------
void AAvatar::TaskCompleted() {
	GetWorldTimerManager().ClearTimer(TaskTimer);
	if (!HasAuthority())
		return;

	if (!IsValid(GoalActor) || !GoalActor) {
		Stop();
	}
	//Once we are done we are no longer working on the task
	IsDoingTask = false;
	//Every task has a cool down period to prevent future tasks
	IsTaskOnCoolDown = true;
	//Set how long we are on cool down for
	if (GetWorld())
		GetWorldTimerManager().SetTimer(TaskCoolDownTimer, this, &AAvatar::EndTaskCooldown, GetCurrentTaskCoolDownDuration(), false);

	switch (GoalAction) {
	case EInteractionType::Use:
		UseTask();
		if (!Cast<UCraftingInfo>(UseObject) || Cast<UCraftingInfo>(UseObject)->GetCraftingAmount() <= 0)
			Stop();
		break;
	case EInteractionType::Attack:
		//Attack
		if (ValidGoal()) {
			FDamageEvent dmgEvent = FDamageEvent();
			GoalActor->TakeDamage(5.f, dmgEvent, GetController(), this);
		}
		else {
			Stop();
		}
		break;
	case EInteractionType::Follow:
		break;
	case EInteractionType::Pick_Up:
		PickUpTask();
		Stop();
		break;
	case EInteractionType::Harvest:
		HarvestTask();
		break;
	default:
		Stop();
		break;
	}
}

//--------------------------------------------------------
//-------------------END TASK COOLDOWN--------------------
void AAvatar::EndTaskCooldown() {
	if (!HasAuthority())
		return;
	IsTaskOnCoolDown = false;
}

//--------------------------------------------------------
//---------------------PICK UP TASK-----------------------
void AAvatar::PickUpTask() {
	if (!HasAuthority())
		return;
	AItem_World* goal = Cast<AItem_World>(GoalActor);
	if (!IsValid(goal)) {
		Stop();
	}
	else {
		AQuintPlayerController* owner = Cast<AQuintPlayerController>(GetOwner());
		if (owner) {
			owner->AddItemToInventory(goal);
		}
	}
}

//--------------------------------------------------------
//----------------------HARVEST TASK----------------------
void AAvatar::HarvestTask() {
	AResourceNode* node = Cast<AResourceNode>(GoalActor);
	if (IsValid(node)) {
		node->HarvestThis(this);
	}
}

//--------------------------------------------------------
//------------------------USE TASK------------------------
void AAvatar::UseTask() {
	if (IsValid(GoalActor) && GoalActor->GetClass()->ImplementsInterface(UInteractable::StaticClass())) {

		if (IInteractable::Execute_UseThis(GoalActor, UseObject, this)) {

		}
		else {
			Stop();
		}
	}
}

//--------------------------------------------------------
//-------------------------COMBAT-------------------------
//--------------------------------------------------------

//--------------------------------------------------------
//------------------REP. DAMAGE RECIVED-------------------
void AAvatar::ReplicateDamageRecived_Implementation(int Amount) {
}

//--------------------------------------------------------
//--------------------SET: IN COMBAT----------------------
void AAvatar::SetIsInCombat(bool Combat) {
	if (!HasAuthority())
		return;
	IsInCombat = Combat;
	if (IsInCombat && GetWorld())
		GetWorldTimerManager().SetTimer(IsInCombatTimer, this, &AAvatar::EndOfCombat, CombatTimeOutSpeed, false);
}

//--------------------------------------------------------
//-------------------END OF COMBAT------------------------
void AAvatar::EndOfCombat() {
	SetIsInCombat(false);
}

//--------------------------------------------------------
//---------------IS TASK COMBAT RELATED-------------------
bool AAvatar::IsTaskCombatTask() {
	return GoalAction == EInteractionType::Attack;
}

/*
-------------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------PUBLIC----------------------------------------------------------------------------------
--------------------------------------------------FUNCTIONS--------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------
*/
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

// Called every frame
void AAvatar::Tick(float DeltaTime){
	
	Super::Tick(DeltaTime);
	if(!HasAuthority())
		return;
	if(ValidTask()){
		FRotator lookAt = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), ValidGoal() ? GoalActor->GetActorLocation() : GoalLocation);
		lookAt = FRotator(0, lookAt.Yaw, 0);
		
		SetActorRotation(FMath::RInterpTo(GetActorRotation(), lookAt, DeltaTime, TurnSpeed));
		//AddActorWorldRotation(rotator);
		//At goal
		if(IsAtGoal()){
			if(!IsValid(GoalActor)){
				Stop();
			}
			else if(lookAt.Equals(GetActorRotation(), 10) && !IsDoingTask && !IsTaskOnCoolDown){
				StartDoingTask();
			}
			//if can't do task, do nothing
		}
		//Am I not doing anything? and am I 
		else{
			//Am I not at goal and doing a task?
			if(IsDoingTask){
				//stop doing task 
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

AQuintPlayerController * AAvatar::GetQuintController()
{
	return Cast<AQuintPlayerController>(GetOwner());
}

// Called to bind functionality to input
void AAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent){
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

//--------------------------------------------------------
//--------------------------TASK--------------------------
//--------------------------------------------------------

//--------------------------------------------------------
//--------------------SET GOAL LOCATION-------------------
void AAvatar::SetLocationGoal(FVector Location) {
	if (!HasAuthority())
		return;
	if (HasAuthority()) {
		Stop();
		GoalLocation = Location;
	}
}

//--------------------------------------------------------
//-------------------SET GOAL ACTOR/ACTION----------------
void AAvatar::SetGoalAndAction(AActor * Goal, EInteractionType Action, UObject* UsingThis) {
	if (!HasAuthority())
		return;
	Stop();
	GoalActor = Goal;
	GoalAction = Action;
	UseObject = UsingThis;
}

//--------------------------------------------------------
//-----------------------VALID TASK-----------------------
bool AAvatar::ValidTask() {
	return ValidGoal() || !GoalLocation.Equals(INVALID_LOCATION);
}

//--------------------------------------------------------
//-----------------CAN DO CURRENT TASK--------------------
bool AAvatar::CanDoCurrentTask() {
	if (IsValid(GoalActor) && GoalActor->GetClass()->ImplementsInterface(UInteractable::StaticClass())) {
		return IInteractable::Execute_IsValidTask(GoalActor, GoalAction, this);
	}
	return !IsValid(GoalActor);
}

//--------------------------------------------------------
//-------------------GET TASK DURATION--------------------
float AAvatar::GetCurrentTaskDuration() {
	switch (GoalAction) {
	case EInteractionType::Attack:
		//Calculate based on weapon
		return .5;
		break;
	case EInteractionType::Harvest:
		//Calculate base on node
		return 1.f;
	case EInteractionType::Use:
		return !Cast<UCraftingInfo>(UseObject) ? 0.1 : Cast<UCraftingInfo>(UseObject)->GetCraftTime();
	default:
		return 0.1;
		break;
	}
}

//--------------------------------------------------------
//------------------TASK COOL DOWN TIME-------------------
float AAvatar::GetCurrentTaskCoolDownDuration() {
	switch (GoalAction) {
	case EInteractionType::Attack:
		//Calculate based on weapon
		return 1.f;
	case EInteractionType::Harvest:
		return .4;
	case EInteractionType::Use:
		return !Cast<UCraftingInfo>(UseObject) ? 0.1 : 0.5;
	default:
		return 0.5;
	}
}

//--------------------------------------------------------
//-----------------HIGHEST TOOL LEVEL OF TYPE-------------
int AAvatar::GetHighestToolLevelOfType(EHarvestType Type) {
	AQuintPlayerController* controller = GetQuintController();
	if (IsValid(controller))
		return controller->GetHighestToolLevelOfType(Type);
	return 0;
}

//--------------------------------------------------------
//------------------------COMBAT--------------------------
//--------------------------------------------------------

//--------------------------------------------------------
//----------------------TAKE DAMAGE-----------------------
float AAvatar::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser){
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

