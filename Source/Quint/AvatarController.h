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
	virtual void Tick(float DeltaTime) override;
	class AAvatar* PlayerAvatar= nullptr;
	AActor* GoalActor = nullptr;
	EInteractionType GoalAction = No_Interaction;
	const FVector INVALID_LOCATION = FVector(-1000);
	FVector GoalLocation = INVALID_LOCATION;
	bool IsDoingTask = false;
	float GetGoalDistance();
	bool IsAtGoal();
	void MoveToLocationOrGoal();
	void Stop();
public:
	void SetLocationGoal(FVector Location);
	void SetGoalAndAction(AActor* Goal, EInteractionType Action);
};
