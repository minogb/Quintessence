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
	class AAvatar* PlayerAvatar= nullptr;
	AActor* GoalActor = nullptr;
	EInteractionType GoalAction = No_Interaction;
	const FVector INVALID_LOCATION = FVector(-1000);
	FVector GoalLocation = INVALID_LOCATION;
	FTimerHandle TaskCoolDownTimer;
	FTimerHandle TaskTimer;
	bool IsDoingTask = false;
	bool IsTaskOnCoolDown = false;
	float TurnSpeed = 2.f;
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
	//how long does current task take to be completed
	float GetCurrentTaskDuration();
	//how long between tasks
	float GetCurrentTaskCoolDownDuration();
	//The build up to complete the task has been completed
	void TaskCompleted();
	//The time between tasks has been completed
	void EndTaskCooldown();
	//Do we have a current task
	bool ValidTask();

public:	

	// Sets default values for this character's properties
	AAvatar();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetLocationGoal(FVector Location);
	void SetGoalAndAction(AActor* Goal, EInteractionType Action);
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual int32 GetAvaliableTasks() override{ return Follow | Trade | Examine; }
	virtual EInteractionType GetDefaultTask() override{ return Follow; }
	
	
};
