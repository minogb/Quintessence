// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
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
ENUM_CLASS_FLAGS( EInteractionType )
class QUINT_API IInteractable {
	GENERATED_BODY()

public:
	//TODO: Prob use something other than the avatar class here
	virtual UObject* UseThis(class AAvatar* Player, UObject* With) {return nullptr;}
	//Returns bitmask
	virtual int32 GetAvaliableTasks() { return No_Interaction; }

	virtual EInteractionType GetDefaultTask() { return No_Interaction; }
};