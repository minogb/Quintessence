// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UnrealNetwork.h"
#include "QuintPlayerState.h"
#include "QuintPlayerController.generated.h"
class AQuintCharacter;
UCLASS(Blueprintable)
class AQuintPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	float MaxGoalDistance = 0.f;
	AActor* Goal = nullptr;
	enum EInteractionType Task;
	bool DoingTask = false;
	bool TaskReady = true;

	FTimerHandle TaskCoolDownTimer = FTimerHandle();
public:

protected:
	static float GetMinRange() { return 120.f; }
	float GetMaxRangeDistance(){ return MaxGoalDistance + GetMinRange();}

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
	void SetTask(AActor* goal, enum EInteractionType task);
	void MoveToGoal();
	void MoveToLocation(FVector location);
	bool IsAtGoal();
	bool IsTaskReadyIfUsed();
	void SetTaskCoolDownTime(float time);
	void TaskCoolDownDone(){ GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "done timer"); TaskReady = true;}
	void DoTask();
	void CompleteTask();
	void StopDoingTask();
	UFUNCTION(BlueprintCallable)
	void FinishedTask() { if(HasAuthority())DoingTask = false; }
	//Can't cast pawn to quint char?  in inline?
	AQuintCharacter* GetPlayerPawn();
	FORCEINLINE class AQuintPlayerState* GetPlayerState() { return Cast<AQuintPlayerState>(PlayerState); }
	
public:
	AQuintPlayerController();
};


