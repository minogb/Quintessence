// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Enumerations.h"
#include "Interactable.generated.h"

#define ECC_Interactable ECC_GameTraceChannel1
/**
 * 
 */
UINTERFACE(MinimalAPI)
class  UInteractable : public UInterface
{
	GENERATED_BODY()
};
UENUM(BlueprintType, Meta = (Bitflags))
enum class EInteractionType : uint8 {
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
protected:
	//Get the rewards from a loot table. Should be called internally only
	TArray<UItem*> GetLootRewards(TArray<FLootStruct>LootTable);
public:
	UFUNCTION(BlueprintNativeEvent)
	bool IsValidTask(EInteractionType Task, class AAvatar* Player = nullptr);
	virtual bool IsValidTask_Implementation(TEnumAsByte<EInteractionType> Task, class AAvatar* Player = nullptr);
	//TODO: Prob use something other than the avatar class here
	//bool IInteractable::IsValidTask(EInteractionType Task, AAvatar* Player)
	UFUNCTION(BlueprintNativeEvent)
	bool UseThis(UObject* With, UObject* Source = nullptr);
	virtual bool UseThis_Implementation(UObject* With, UObject* Source = nullptr) { return false; }
	//Returns bitmask
	UFUNCTION(BlueprintNativeEvent)
	uint8 GetAvaliableTasks();
	virtual uint8 GetAvaliableTasks_Implementation() { return (uint8)EInteractionType::No_Interaction; }

	UFUNCTION(BlueprintNativeEvent)
	EInteractionType GetDefaultTask();
	virtual EInteractionType GetDefaultTask_Implementation() { return EInteractionType::No_Interaction; }
	UFUNCTION(BlueprintNativeEvent)
	float GetSize();
	virtual float GetSize_Implementation();
};