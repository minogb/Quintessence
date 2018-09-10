// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractableInterface : public UInterface
{
	GENERATED_BODY()
};
UENUM(BlueprintType, Meta = (Bitflags))
enum EInteractionType {
	No_Interaction UMETA(DisplayName = "None"),
	Move_Here UMETA(DisplayName = "Walk Here"),
	Examine UMETA(DisplayName = "Examine"),
	Attack UMETA(DisplayName = "Attack"),
	Follow UMETA(DisplayName = "Follow"),
	Trade UMETA(DisplayName = "Trade"),
	Talk UMETA(DisplayName = "Talk"),
	Pick_Up UMETA(DisplayName = "Pick Up"),
	Harvest UMETA(DisplayName = "Harvest"),
	Use UMETA(DisplayName = "Use")
};
/**
 * 
 */
class QUINT_API IInteractableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual int32 GetAvaliableTasks() { return No_Interaction; }

	virtual EInteractionType GetDefaultTask() { return No_Interaction; }

	virtual void UseObject() {}
};
