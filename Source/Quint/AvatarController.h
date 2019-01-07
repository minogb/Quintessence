// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Interactable.h"
#include "AvatarController.generated.h"
/**
 * 
 */
UCLASS()
class QUINT_API AAvatarController : public AAIController
{
	GENERATED_BODY()
private:
	class AAvatar* PlayerAvatar= nullptr;
	AActor* GoalActor = nullptr;
	EInteractionType GoalAction = No_Interaction;
	const FVector INVALID_LOCATION = FVector(-1000);
	FVector GoalLocation = INVALID_LOCATION;
	FTimerHandle TaskCoolDownTimer;
	FTimerHandle TaskTimer;
	bool IsDoingTask = false;
	bool IsTaskOnCoolDown = false;


	virtual void Tick(float DeltaTime) override;
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
	void SetLocationGoal(FVector Location);
	void SetGoalAndAction(AActor* Goal, EInteractionType Action);
};
