// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SkillStructure.h"
#include "Enumerations.generated.h"

#define ECC_Interactable ECC_GameTraceChannel1
#define ECC_Floor ECC_GameTraceChannel2
#define ECC_ProjectileBlock ECC_GameTraceChannel3
#define DT_PHYSICAL EDamageType::DT_DULL | EDamageType::DT_BLUNT | EDamageType::DT_CLEAVE | EDamageType::DT_PEIRCING
#define DT_MAGIC EDamageType::DT_ELECTRICAL | EDamageType::DT_FIRE | EDamageType::DT_WATER | EDamageType::DT_EARTH | EDamageType::DT_WIND

class UItem;

UENUM(BlueprintType)
enum class EDamageType : uint8 {
	DT_NONE UMETA(DisplayName = "NONE"),
	//Physical
	DT_DULL UMETA(DisplayName = "DULL"),
	DT_BLUNT UMETA(DisplayName = "BLUNT"),
	DT_CLEAVE UMETA(DisplayName = "CLEAVE"),
	DT_PEIRCING UMETA(DisplayName = "PEIRCING"),
	//Magical
	DT_ELECTRICAL UMETA(DisplayName = "ELECTRICAL"),
	DT_FIRE UMETA(DisplayName = "FIRE"),
	DT_WATER UMETA(DisplayName = "WATER"),
	DT_EARTH UMETA(DisplayName = "EARTH"),
	DT_WIND UMETA(DisplayName = "WIND")
};
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
struct FDamageStruct : public FTableRowBase {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamageAmount = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDamageType DamageType;
	//0-1% chance of glancing
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GlanceChance = .125;
	//0-1% minimum value to reduce damage by
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GlanceMultiplierFloor = 0.25;
	//0-1% maximum value to reduce damage by
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GlanceMultiplierCeiling = 0.5;
	//0-1% chance of criting
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CritChance = .125;
	//Minimum amount damage should be multiplyed by after crit
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CritMultiplierFloor = 2;
	//Minimum amount damage should be multiplyed by after crit
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CritMultiplierCeiling = 2;
	//What skill should be rewarded for damage delt
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESkillType Skill;
	//What skill should be rewarded for damage delt
	UItem* Weapon;
	//Calculate damage after glance/crits. Chance will be 1 or 0 for respective values
	void CollapseProbility();
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
USTRUCT(BlueprintType)
struct FExpRewardStruct {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESkillType Skill;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Exp = 0;
};
//TODO: Add ?XP reward info?, add Craft time?
USTRUCT(BlueprintType)
struct FCraftingStruct : public FTableRowBase {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FExpRewardStruct Experience;
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