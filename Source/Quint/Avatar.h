// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/Interactable.h"
#include "Enumerations.h"
#include "Avatar.generated.h"

UENUM(BlueprintType, Meta = (Bitflags))
enum class EGoalType : uint8 {
	GT_INVALID UMETA(DisplayName = "None"),
	GT_ACTOR UMETA(DisplayName = "Actor"),
	GT_LOCATION UMETA(DisplayName = "Location")
};
USTRUCT(BlueprintType)
struct FGoalPlayerStruct {
	GENERATED_BODY()
	//invalid location for use
	static FVector GetInvalidLocation() { return FVector(-1000); }
	//What our actor is after
	AActor* Actor = nullptr;
	//What our actor should use
	UObject* UseObject = nullptr;
	//How our actor should act
	EInteractionType Action = EInteractionType::No_Interaction;
	//Where our actor should be
	FVector Location = GetInvalidLocation();

	bool Valid() { return IsValid(Actor) || !Location.Equals(GetInvalidLocation()); }
	bool ValidActor() { return IsValid(Actor); }
	EGoalType GetGoalType() { return IsValid(Actor) ? EGoalType::GT_ACTOR : !Location.Equals(GetInvalidLocation()) ? EGoalType::GT_LOCATION : EGoalType::GT_INVALID; }
	bool GetLocation(FVector& Loc) { Loc = IsValid(Actor) ? Actor->GetActorLocation() : Location; return Valid(); }
	void Invalidate() { Actor = nullptr; UseObject = nullptr; Action = EInteractionType::No_Interaction; Location = GetInvalidLocation();}
};
UCLASS()
class QUINT_API AAvatar : public ACharacter, public IInteractable {
	GENERATED_BODY()
protected:
	//how fast our character should turn
	UPROPERTY(Replicated)
	float TurnSpeed = 5.f;
	//Character Health
	UPROPERTY(Replicated)
	float Health = 100.f;

	UPROPERTY(Replicated)
	float MaxHealth = 100.f;

	UPROPERTY(Replicated)
	TArray<UObject*> Effects;

	FGoalPlayerStruct Goal;

	//Timer: How long action should take
	FTimerHandle TaskTimer;
	//Timer: How long inbetween actions
	FTimerHandle TaskCoolDownTimer;
	//Timer: Are we in combat?
	FTimerHandle IsInCombatTimer;
	//Are in in the middle of a task
	UPROPERTY(Replicated)
	bool IsDoingTask = false;
	//Are we inbtween doing tasks?
	bool IsTaskOnCoolDown = false;
	//Percent of task completed: usufull for UI
	UPROPERTY(Replicated)
	float PercentTaskCompleted = 0.f;
	//Are we in combat
	UPROPERTY(Replicated)
	bool IsInCombat = false;
	//How long we should be in combat after init it
	float CombatTimeOutSpeed = 5.0;

	//--------------------------------------------------------
	//------------------------FUNCTIONS-----------------------
	//--------------------------------------------------------

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//--------------------------------------------------------
	//---------------------------GOAL-------------------------
	//--------------------------------------------------------

	//how close do we need to get to the goal
	float GetGoalDistance();
	//are we are the goal
	bool IsAtGoal();
	//Move to the desired goal
	void MoveToLocationOrGoal();

	//--------------------------------------------------------
	//---------------------------TASK-------------------------
	//--------------------------------------------------------

	//Start task timer
	void StartDoingTask();
	//Stop all takss and movement
	void Stop();
	//Interupt if we are doing a task
	void InteruptTask();
	//The build up to complete the task has been completed
	void TaskCompleted();
	//The time between tasks has been completed
	void EndTaskCooldown();
	//Function for picking up goal
	void PickUpTask();
	//Function for harvesting goal
	void HarvestTask();
	//Function for using goal with use object
	void UseTask();
	void AttackTask();

	//--------------------------------------------------------
	//-------------------------COMBAT-------------------------
	//--------------------------------------------------------

	//Client:Recivie damage notification
	UFUNCTION(NetMulticast,Unreliable)
	void ReplicateDamageRecived(int Amount);
	void ReplicateDamageRecived_Implementation(int Amount);
	//Set if we are in combat
	void SetIsInCombat(bool Combat = true);
	//End combat timer
	void EndOfCombat();
	//Is our task combat related? Attacking? Casting?
	bool IsTaskCombatTask();

	//--------------------------------------------------------
	//-------------------------Effects------------------------
	//--------------------------------------------------------
	//TODO: Should all of these effect functions be exposed to public?
	//Get Effects - including equipment
	TArray<UObject*> GetEffects();
	//Incoming damage
	UFUNCTION(BlueprintCallable)
	void DelegateOnIncomingDamage(FDamageStruct& Damage, UObject* DamageCauser, AController* CauserController);
	//Damage Taken
	UFUNCTION(BlueprintCallable)
	void DelegateOnDamageTaken(FDamageStruct& Damage, UObject* DamageCauser, AController* CauserController);
	//Damge outgoing
	UFUNCTION(BlueprintCallable)
	void DelegateOnOutgoingDamage(FDamageStruct& Damage, UObject* DamageTarget);
	//Damage delt
	UFUNCTION(BlueprintCallable)
	void DelegateOnDamageDelt(FDamageStruct& Damage, UObject* DamageTarget);
	//Attack Speed
	UFUNCTION(BlueprintCallable)
	void DelegateOnActionSpeedCalculation(float& Speed, EInteractionType Action);
	//Attack Speed
	UFUNCTION(BlueprintCallable)
	void DelegateOnCoolDownCalculation(float& Speed, EInteractionType Action);
	//Skill Level
	UFUNCTION(BlueprintCallable)
	int DelegateSkillLevel(ESkillType Skill, int Level);
public:	
	// Sets default values for this character's properties
	AAvatar();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Get controller
	UFUNCTION(BlueprintCallable)
	class AQuintPlayerController* GetQuintController();

	//--------------------------------------------------------
	//---------------------------TASK-------------------------
	//--------------------------------------------------------
	//Set our goal as lokcation
	void SetLocationGoal(FVector Location);
	//Set our goal as actor and action
	void SetGoalAndAction(AActor* GoalActor, EInteractionType Action, UObject* UsingThis = nullptr);
		
	//Can we do the asigned task?
	UFUNCTION(Blueprintable)
	bool CanDoCurrentTask();

	//--------------------------GETS--------------------------
	//how long does current task take to be completed
	UFUNCTION(BlueprintCallable)
	float GetCurrentTaskDuration();

	//how long between tasks
	UFUNCTION(BlueprintCallable)
	float GetCurrentTaskCoolDownDuration();

	//Are we doing a task?
	UFUNCTION(BlueprintCallable)
	bool GetIsDoingTask() { return IsDoingTask; }

	//Percentage of task completed
	UFUNCTION(BlueprintCallable)
	float GetPercentTaskDone() { return PercentTaskCompleted; }

	//Get the highest tool level of harvest type
	UFUNCTION(BlueprintCallable)
	int GetHighestToolLevelOfType(EHarvestType Type);

	//--------------------------------------------------------
	//-------------------------COMBAT-------------------------
	//--------------------------------------------------------


	//Get the attack speed of the current weapon
	UFUNCTION(BlueprintCallable)
	float CalculateAttackTime();

	//Get the cool down of the current weapon
	UFUNCTION(BlueprintCallable)
	float CalculateAttackCooldownTime();

	//TODO: update with get damage type ? Get the damage of the current weapon
	UFUNCTION(BlueprintCallable)
	FDamageStruct CalculateAttackDamage();

	//Get the range of the current weapon
	UFUNCTION(BlueprintCallable)
	float CalculateWeaponRange();
	//--------------------------GETS--------------------------

	//Get our current weapon
	UFUNCTION(BlueprintCallable)
	UItem* GetWeapon();

	//Are we in combat?
	UFUNCTION(BlueprintCallable)
	bool GetIsInCombat() { return IsInCombat; }

	//Get our current health
	UFUNCTION(BlueprintCallable)
	float GetHealth() { return Health; }

	void SetHealth(float Amount) { Health = Amount < MaxHealth ? Amount : MaxHealth; }

	//Get our health as a percent
	UFUNCTION(BlueprintCallable)
	float GetHealthPercent() { return Health / MaxHealth; }


	//Get our skill level
	UFUNCTION(BlueprintCallable, Blueprintpure)
	int GetSkillLevel(ESkillType Skill);
	//--------------------------------------------------------
	//-----------------INTERACTABLE INTERFACE-----------------
	//--------------------------------------------------------
	virtual uint8 GetAvaliableTasks_Implementation() override { return (uint8)EInteractionType::Follow | (uint8)EInteractionType::Trade | (uint8)EInteractionType::Examine | (uint8)EInteractionType::Attack; }
	virtual EInteractionType GetDefaultTask_Implementation() override { return EInteractionType::Attack; }
	virtual void ApplyDamage_Implementation(UPARAM(ref)FDamageStruct& Damage, AActor* DamageCauser, AController* CauserController = nullptr) override;
	virtual void ReturnDamageDelt_Implementation(FDamageStruct Damage, AActor* DamagedActor, bool IsKillingBlow) override;
};
