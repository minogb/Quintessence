// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UnrealNetwork.h"
#include "QuintPlayerState.h"
#include "QuintPlayerController.generated.h"

UCLASS(Blueprintable)
class AQuintPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	float MaxGoalDistance = 0.f;
	AActor* Goal;
	enum EInteractionType Task;
	bool DoingTask;
	FTimerHandle TaskCoolDownTimer;
public:

protected:
	//Action distance calculation needs to be round 120
	static float GetMinRange() { return 120.f; }
	float GetMaxRangeDistance(){ return MaxGoalDistance;}

	// Begin PlayerController interface
	virtual void Tick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface


	/** Navigate player to the current touch location. */
	void MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location);
	
	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();
	
	//After the anim is done playing apply damage
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
	void ActionAnimDone();
	/** Navigate player to the given world location. */
	UFUNCTION(Server, Reliable, WithValidation)
	void SetNewMoveDestination(const FVector DestLocation, AActor* DestActor);
	//Set the task at hand
	void SetTask(AActor* goal, enum EInteractionType task);
	//Move to goal after set
	void MoveToGoal();
	//if no goal just move there
	void MoveToLocation(FVector location);
	//Are we at our goal already?
	bool IsAtGoal();
	//We use a universal timer for tasks
	bool IsTaskReadyIfUsed();
	//Set the timer for the task
	void SetTaskCoolDownTime(float time);
	//The timer has finisshed and we can reset tasks
	void TaskCoolDownDone(){ TaskCoolDownTimer.Invalidate();}
	//try to do the task given to us
	void DoTask();
	//Cancle any current task
	void StopDoingTask();
	void DamageGoal();
	//Can't cast pawn to quint char?  in inline?
	class AQuintCharacter* GetPlayerPawn();
	FORCEINLINE class AQuintPlayerState* GetPlayerState() { return Cast<AQuintPlayerState>(PlayerState); }
	
public:
	AQuintPlayerController();
};


