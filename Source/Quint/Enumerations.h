// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Enumerations.generated.h"

class UItem;
UENUM(BlueprintType)
enum class EHarvestType : uint8 {
	HT_NONE UMETA(DisplayName = "NONE"),
	HT_MINING UMETA(DisplayName = "MINING")
};

UENUM(BlueprintType, Meta = (Bitflags))
enum class EItemAction : uint8 {
	IA_NONE UMETA(DisplayName = "None"),
	IA_EQUIP UMETA(DisplayName = "Equip"),
	IA_UNEQUIP UMETA(DisplayName = "Unequip"),
	IA_DROP UMETA(DisplayName = "Drop"),
	IA_USE UMETA(DisplayName = "Use")
};

UENUM(BlueprintType, Meta = (Bitflags))
enum class ESkillType : uint8 {
	ST_NONE UMETA(DisplayName = "None")
};

UENUM(BlueprintType, Meta = (Bitflags))
enum class ECraftingToolType : uint8 {
	CTT_NONE UMETA(DisplayName = "None")
};
UENUM(BlueprintType, Meta = (Bitflags))
enum class ECraftingStationType : uint8 {
	CST_NONE UMETA(DisplayName = "None"),
	CST_SMELTING UMETA(DisplayName = "Smeltery")
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
	ECraftingStationType CraftingLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECraftingToolType RequiredTool;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FItemCraftingStruct> Input;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemCraftingStruct Output;
};
USTRUCT(BlueprintType)
struct FLootStruct {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UItem> Reward;
	//Range from 0 to 1. if 0 always
	UPROPERTY(EditAnywhere)
	float ChancePercent;
	UPROPERTY(EditAnywhere)
	int MinReward;
	UPROPERTY(EditAnywhere)
	int MaxReward;
	FLootStruct() {
		MinReward = 1;
		MaxReward = 1;
		ChancePercent = 0;
	}
	UItem* GetReward(int booster = 0);
};