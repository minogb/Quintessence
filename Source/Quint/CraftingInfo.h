// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Enumerations.h"
#include "CraftingInfo.generated.h"

/**
 * 
 */
UENUM(BlueprintType, Meta = (Bitflags))
enum class ECraftingToolType : uint8 {
	CTT_NONE UMETA(DisplayName = "None")
};
UENUM(BlueprintType, Meta = (Bitflags))
enum class ECraftingStationType : uint8 {
	CST_NONE UMETA(DisplayName = "None"),
	CST_SMELTING UMETA(DisplayName = "Smeltery"),
	CST_WORKBENCH UMETA(DisplayName = "Workbench")
};

USTRUCT(BlueprintType)
struct FItemCraftingStruct {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UItem> Item;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Count = 1;
};
//TODO: Add ?XP reward info?, add Craft time?
USTRUCT(BlueprintType)
struct FCraftingStruct : public FTableRowBase {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSkillLevelStruct> SkillRequired;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FExpRewardStruct> ExpReward;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECraftingStationType CraftingLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECraftingToolType RequiredTool;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FItemCraftingStruct> Input;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemCraftingStruct Output;
};
UCLASS(Blueprintable)
class QUINT_API UCraftingInfo : public UObject {
	GENERATED_BODY()
	int Amount;
	FCraftingStruct CraftingRecipe;
	float CraftingTime;
	float CalculateCraftingTime();
public:
	UFUNCTION(BlueprintCallable)
	void InitObject(FCraftingStruct Recipe, int CraftingAmount);
	UFUNCTION(BlueprintCallable)
	FCraftingStruct	GetCraftingRecipe() { return CraftingRecipe; }
	UFUNCTION(BlueprintCallable)
	int	GetCraftingAmount() { return Amount; }
	UFUNCTION(BlueprintCallable)
	float GetCraftTime() { return CraftingTime; }
	void DecrimentCraftingAmount() { Amount--; }
};