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
#include "Interfaces/WeaponInterface.h"
#include "Interfaces/EffectInterface.h"
#include "CraftingInfo.h"
#include "Kismet/KismetMathLibrary.h"

#define PrintToScreen(x) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, FString(x));}
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

	float bonusDistance = 32.f;
	if (IsValid(GoalActor) && GoalActor->GetClass()->ImplementsInterface(UInteractable::StaticClass())) {

		bonusDistance += IInteractable::Execute_GetSize(GoalActor);
	}
	switch (GoalAction) {
	case EInteractionType::Attack:
		//Calculate based on weapon
		return bonusDistance + CalculateWeaponRange();
	default:
		return bonusDistance + 32.f;
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
		AttackTask();
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

void AAvatar::AttackTask(){
	if (ValidGoal()) {
		//GoalActor->TakeDamage(Damage.DamageAmount, dmgEvent, GetQuintController(), this);
		if (GoalActor->GetClass()->ImplementsInterface(UInteractable::StaticClass())) {
			FDamageEvent dmgEvent = FDamageEvent();
			FDamageStruct Damage = CalculateAttackDamage();
			//Deligate attack to weapon
			if (GetWeapon() && GetWeapon()->GetClass()->ImplementsInterface(UWeaponInterface::StaticClass())) {
				//Let the weapon deal damage
				IWeaponInterface::Execute_UseWeapon(GetWeapon(), this, Damage, GoalActor);
			}
			//If no weapon deal your fists
			else {
				//Delegate damage outgoing
				IInteractable::Execute_ApplyDamage(GoalActor, Damage, this, GetQuintController());
			}
		}
		else {
			Stop();
			return;
		}
	}
	else {
		Stop();
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

//--------------------------------------------------------
//-------------------------Effects------------------------
//--------------------------------------------------------

//--------------------------------------------------------
//------------------Get List of Effects-------------------
TArray<UObject*> AAvatar::GetEffects() {
	TArray<UObject*> retVal = TArray<UObject*>(Effects);
	if (IsValid(GetQuintController()))
		retVal.Append(GetQuintController()->GetEquipmentAsList());
	return retVal;
}

//--------------------------------------------------------
//------------------On Incoming Damage--------------------
void AAvatar::DelegateOnIncomingDamage(FDamageStruct & Damage, UObject * DamageCauser, AController * CauserController) {
	for (UObject*current : GetEffects()) {
		if (IsValid(current) && current->GetClass()->ImplementsInterface(UEffectInterface::StaticClass())) {
			IEffectInterface::Execute_OnIncomingDamage(current, Damage, DamageCauser, CauserController);
		}
	}
}

//--------------------------------------------------------
//---------------------On Damage Taken--------------------
void AAvatar::DelegateOnDamageTaken(FDamageStruct & Damage, UObject * DamageCauser, AController * CauserController) {
	for (UObject*current : GetEffects()) {
		if (IsValid(current) && current->GetClass()->ImplementsInterface(UEffectInterface::StaticClass())) {
			IEffectInterface::Execute_OnDamageTaken(current, Damage, DamageCauser, CauserController);
		}
	}

}

//--------------------------------------------------------
//------------------On Outgoing Damage--------------------
void AAvatar::DelegateOnOutgoingDamage(FDamageStruct & Damage, UObject * DamageTarget) {
	for (UObject*current : GetEffects()) {
		if (IsValid(current) && current->GetClass()->ImplementsInterface(UEffectInterface::StaticClass())) {
			IEffectInterface::Execute_OnOutgoingDamage(current, Damage, DamageTarget);
		}
	}

}

//--------------------------------------------------------
//----------------------On Damage Delt--------------------
void AAvatar::DelegateOnDamageDelt(FDamageStruct & Damage, UObject * DamageTarget) {
	for (UObject*current : GetEffects()) {
		if (IsValid(current) && current->GetClass()->ImplementsInterface(UEffectInterface::StaticClass())) {
			IEffectInterface::Execute_OnDamageDelt(current, Damage, DamageTarget);
		}
	}

}

void AAvatar::DelegateOnActionSpeedCalculation(float & Speed, EInteractionType Action) {
	for (UObject*current : GetEffects()) {
		if (IsValid(current) && current->GetClass()->ImplementsInterface(UEffectInterface::StaticClass())) {
			IEffectInterface::Execute_OnActionSpeedCalculation(current, Speed, Action);
		}
	}
}

void AAvatar::DelegateOnCoolDownCalculation(float & Speed, EInteractionType Action) {
	for (UObject*current : GetEffects()) {
		if (IsValid(current) && current->GetClass()->ImplementsInterface(UEffectInterface::StaticClass())) {
			IEffectInterface::Execute_OnActionCoolDownCalculation(current, Speed, Action);
		}
	}
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
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_ProjectileBlock, ECollisionResponse::ECR_Ignore);
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
	DOREPLIFETIME(AAvatar, MaxHealth);
	DOREPLIFETIME(AAvatar, Effects);
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
	bool retVal = false;
	switch (GoalAction) {
	case EInteractionType::Attack:
		if (GetWeapon() && GetWeapon()->GetClass()->ImplementsInterface(UWeaponInterface::StaticClass())) {
			retVal = IWeaponInterface::Execute_CanUseWeapon(GetWeapon(),this);
		}
		//TODO: Is oponent in an attackable state
		retVal = true;
		break;
	default:
		if (IsValid(GoalActor) && GoalActor->GetClass()->ImplementsInterface(UInteractable::StaticClass())) {
			retVal = IInteractable::Execute_IsValidTask(GoalActor, GoalAction, this);
		}
		else
			retVal = !IsValid(GoalActor);
		break;
	}
	return retVal;
}

//--------------------------------------------------------
//-------------------GET TASK DURATION--------------------
float AAvatar::GetCurrentTaskDuration() {
	float retVal = 0;
	switch (GoalAction) {
	case EInteractionType::Attack:
		retVal = CalculateAttackTime();
		break;
	case EInteractionType::Harvest:
		//TODO:
		//Calculate base on node
		retVal = 1.f;
		break;
	case EInteractionType::Use:
		retVal = !Cast<UCraftingInfo>(UseObject) ? 0.1 : Cast<UCraftingInfo>(UseObject)->GetCraftTime();
		break;
	default:
		retVal = 0.1;
		break;
	}
	DelegateOnActionSpeedCalculation(retVal, GoalAction);
	return retVal;
}

//--------------------------------------------------------
//------------------TASK COOL DOWN TIME-------------------
float AAvatar::GetCurrentTaskCoolDownDuration() {
	float retVal = 0;
	switch (GoalAction) {
	case EInteractionType::Attack:
		retVal = CalculateAttackCooldownTime();
		break;
	case EInteractionType::Harvest:
		//TODO:
		retVal = .4;
		break;
	case EInteractionType::Use:
		retVal = !Cast<UCraftingInfo>(UseObject) ? 0.1 : 0.5;
		break;
	default:
		retVal = 0.5;
		break;
	}
	DelegateOnActionSpeedCalculation(retVal, GoalAction);
	return retVal;
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
//------------------CALC WEAPON SPEED---------------------
float AAvatar::CalculateAttackTime(){
	float retVal = 0.f;
	if (GetWeapon() && GetWeapon()->GetClass()->ImplementsInterface(UWeaponInterface::StaticClass())) {
		retVal = IWeaponInterface::Execute_GetWeaponAttackDuration(GetWeapon());
	}
	//Calculate Unarmed
	if (retVal <= 0.f) {
		retVal = .5;
	}
	//TODO:
	//Calculate Bonus
	return retVal;
}

//--------------------------------------------------------
//----------------CALC WEAPON COOLDOWN--------------------
float AAvatar::CalculateAttackCooldownTime(){
	float retVal = 0.f;
	if (GetWeapon() && GetWeapon()->GetClass()->ImplementsInterface(UWeaponInterface::StaticClass())) {
		retVal = IWeaponInterface::Execute_GetWeaponAttackCooldown(GetWeapon());
	}
	//Calculate Unarmed
	if (retVal <= 0.f) {
		retVal = .5;
	}
	//TODO:
	//Calculate Bonus
	return retVal;
}

//--------------------------------------------------------
//-----------------CALC WEAPON DAMAGE---------------------
FDamageStruct AAvatar::CalculateAttackDamage() {
	FDamageStruct retVal;
	if (GetWeapon() && GetWeapon()->GetClass()->ImplementsInterface(UWeaponInterface::StaticClass())) {
		IWeaponInterface::Execute_GetDamageStruct(GetWeapon(),retVal);
	}
	//TODO:
	//Calculate Unarmed
	else{
		retVal.DamageAmount = 1.f;
		retVal.DamageType = EDamageType::DT_DULL;
	}
	//TODO:
	//Calculate Bonus
	DelegateOnOutgoingDamage(retVal, GoalActor);
	return retVal;
}

//--------------------------------------------------------
//------------------CALC WEAPON RANGE---------------------
float AAvatar::CalculateWeaponRange() {
	float retVal = 0.f;
	if (GetWeapon() && GetWeapon()->GetClass()->ImplementsInterface(UWeaponInterface::StaticClass())) {
		retVal = IWeaponInterface::Execute_GetWeaponRange(GetWeapon());
	}
	//Calculate Unarmed
	if (retVal <= 0.f) {
		retVal = 32.f;
	}
	//TODO:
	//Calculate Bonus
	return retVal;
}

//--------------------------------------------------------
//-----------------GET CURRENT WEAPON---------------------
UItem* AAvatar::GetWeapon() {
	return IsValid(GetQuintController()) ? GetQuintController()->GetEquipment(EEquipmentSlot::ES_WEAPON) : nullptr;
}

void AAvatar::ApplyDamage_Implementation(UPARAM(ref)FDamageStruct& Damage, AActor * DamageCauser, AController * CauserController){
	if (!HasAuthority())
		return;
	SetIsInCombat(true);
	//Delegate on incoming damage before taking damage
	DelegateOnIncomingDamage(Damage, DamageCauser, CauserController);
	Damage.CollapseProbility();
	Damage.DamageAmount = (Health - Damage.DamageAmount) >= 0.f ? Damage.DamageAmount : Health;
	//Delegete on damage taken events
	DelegateOnDamageTaken(Damage, DamageCauser, CauserController);
	Health -= Damage.DamageAmount;
	//Tell the damage causes how much they damaged us
	if (IsValid(DamageCauser) && DamageCauser->GetClass()->ImplementsInterface(UInteractable::StaticClass())) {
		IInteractable::Execute_ReturnDamageDelt(DamageCauser, Damage, this, Health<=0);
	}
	//TODO Replicate to clients damagestruct
	if (Health <= 0.f) {
		Destroy(true);
	}
}

void AAvatar::ReturnDamageDelt_Implementation(FDamageStruct Damage, AActor * DamagedActor, bool IsKillingBlow){
	if (GetQuintController()) {
	}
	//Delegate damage delt
	DelegateOnDamageDelt(Damage, DamagedActor);
	if (GetQuintController()) {
		GetQuintController()->AddExperience(Damage.Skill, Damage.DamageAmount * (3.14159265359 / 2));
		AAvatar* Other = Cast<AAvatar>(DamagedActor);
		if(IsKillingBlow)
			GetQuintController()->AddExperience(Damage.Skill, Other->MaxHealth/10 * 3.14159265359);
	}
}