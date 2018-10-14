// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WorldController.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class QUINT_API AWorldController : public APlayerController
{
protected:
	GENERATED_BODY()
	FORCEINLINE class IPawnInterface* GetPlayerPawn();
	/** Navigate player to the current touch location. */
	void MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location);
	
	void SetDestinationHelper(FHitResult HitResult);
	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();
	/** Navigate player to the given world location. */
	UFUNCTION(Server, Reliable, WithValidation)
	void SetNewMoveDestination(const FVector DestLocation, AActor* DestActor);
	// Begin PlayerController interface
	virtual void Tick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

public:
	
	AWorldController();
	virtual void BeginPlay() override;
};
