// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interactable.h"
#include "Avatar.generated.h"

#define ECC_Interactable ECC_GameTraceChannel1
UCLASS()
class QUINT_API AAvatar : public ACharacter, public IInteractable{
	GENERATED_BODY()

protected:
	AActor* GoalActor = nullptr;
	EInteractionType GoalAction = No_Interaction;
	FVector GoalLocation = INVALID_LOCATION;

	const FVector INVALID_LOCATION = FVector(-1000);
	FTimerHandle TaskCoolDownTimer;
	
	FTimerHandle TaskTimer;
	UPROPERTY(Replicated, BlueprintReadOnly)
	bool IsDoingTask = false;
	bool IsTaskOnCoolDown = false;

	//UPROPERTY(Replicated)
	float TurnSpeed = 2.f;

	UPROPERTY(Replicated, BlueprintReadOnly)
	float Health = 10.f;
	
	UPROPERTY(Replicated, BlueprintReadOnly)
	float PercentTaskCompleted = 0.f;

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
	//Replication
	UFUNCTION(NetMulticast,Unreliable)
	void ReplicateDamageRecived(int Amount);
public:	
	// Sets default values for this character's properties
	AAvatar();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetLocationGoal(FVector Location);
	void SetGoalAndAction(AActor* Goal, EInteractionType Action);
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;
	//Valids

	//Do we have a current task
	UFUNCTION(BlueprintCallable)
	bool ValidTask();
	UFUNCTION(BlueprintCallable)
	bool ValidGoal(){ return GoalActor && IsValid(GoalActor);}

	//GETS
	virtual int32 GetAvaliableTasks() override{ return Follow | Trade | Examine; }
	virtual EInteractionType GetDefaultTask() override{ return Attack; }

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
};
