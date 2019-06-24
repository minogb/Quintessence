// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interactable.h"
#include "Enumerations.h"
#include "Avatar.generated.h"

#define ECC_Interactable ECC_GameTraceChannel1
UCLASS()
class QUINT_API AAvatar : public ACharacter, public IInteractable {
	GENERATED_BODY()

protected:
	AActor* GoalActor = nullptr;
	UObject* UseObject = nullptr;
	EInteractionType GoalAction = EInteractionType::No_Interaction;
	const FVector INVALID_LOCATION = FVector(-1000);
	FVector GoalLocation = INVALID_LOCATION;

	FTimerHandle TaskCoolDownTimer;
	FTimerHandle IsInCombatTimer;
	
	FTimerHandle TaskTimer;
	UPROPERTY(Replicated)
	bool IsDoingTask = false;
	bool IsTaskOnCoolDown = false;

	UPROPERTY(Replicated)
	float TurnSpeed = 5.f;

	UPROPERTY(Replicated)
	float Health = 10.f;
	
	UPROPERTY(Replicated)
	float PercentTaskCompleted = 0.f;

	
	UPROPERTY(Replicated)
	bool IsInCombat = false;
	float CombatTimeOutSpeed = 5.0;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//how close do we need to get to the goal
	float GetGoalDistance();
	//are we are the goal
	bool IsAtGoal();
	//Move to the desired goal
	void MoveToLocationOrGoal();
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
	void PickUpTask();
	void HarvestTask();
	void UseTask();
	//Replication
	UFUNCTION(NetMulticast,Unreliable)
	void ReplicateDamageRecived(int Amount);
	void SetIsInCombat(bool Combat = true);
	void EndOfCombat();
	bool IsTaskCombatTask();
public:	
	// Sets default values for this character's properties
	AAvatar();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetLocationGoal(FVector Location);
	void SetGoalAndAction(AActor* Goal, EInteractionType Action, UObject* UsingThis = nullptr);
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;
	//Valids

	//Do we have a current task
	UFUNCTION(BlueprintCallable)
	bool ValidTask();
	UFUNCTION(Blueprintable)
	bool CanDoCurrentTask();
	UFUNCTION(BlueprintCallable)
	bool ValidGoal(){ return IsValid(GoalActor);}

	//GETS
	UFUNCTION(BlueprintCallable)
	int GetHighestToolLevelOfType(EHarvestType Type);
	virtual uint8 GetAvaliableTasks_Implementation() override{ return (uint8)EInteractionType::Follow | (uint8)EInteractionType::Trade | (uint8)EInteractionType::Examine | (uint8)EInteractionType::Attack; }
	virtual EInteractionType GetDefaultTask_Implementation() override{ return EInteractionType::Follow; }

	UFUNCTION(BlueprintCallable)
	float GetHealth(){ return Health; }
	UFUNCTION(BlueprintCallable)
	float GetHealthPercent(){ return Health / 10; }
	//how long does current task take to be completed
	UFUNCTION(BlueprintCallable)
	float GetCurrentTaskDuration();
	//how long between tasks
	UFUNCTION(BlueprintCallable)
	float GetCurrentTaskCoolDownDuration();

	UFUNCTION(BlueprintCallable)
	bool GetIsDoingTask(){return IsDoingTask;}
	UFUNCTION(BlueprintCallable)
	float GetPercentTaskDone(){return PercentTaskCompleted;}
	UFUNCTION(BlueprintCallable)
	bool GetIsInCombat(){return IsInCombat;}
	class AQuintPlayerController* GetQuintController();
};
