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
enum class EAssemblyComponentType : uint8 {
	ECT_NONE UMETA(DisplayName = "Invalid Component"),
	ECT_S_BLADE UMETA(DisplayName = "Short Blade Component"),
	ECT_M_BLADE UMETA(DisplayName = "Medium Blade Component"),
	ECT_L_BLADE UMETA(DisplayName = "Large Blade Component"),
	ECT_H_BLADE UMETA(DisplayName = "Heavy Blade Component"),

	ECT_HAMMER_HEAD UMETA(DisplayName = "Hammer Head Component"),
	ECT_L_HAMMER_HEAD UMETA(DisplayName = "Large Hammer Head Component"),

	ECT_AXE_HEAD UMETA(DisplayName = "Axe Head Component"),
	ECT_PICK_AXE_HEAD UMETA(DisplayName = "Pick Axe Head Component"),

	ECT_S_POMMEL UMETA(DisplayName = "Small Pommel Component"),
	ECT_M_POMMEL UMETA(DisplayName = "Medium Pommel Component"),
	ECT_L_POMMEL UMETA(DisplayName = "Large Pommel Component"),

	ECT_S_GRIP UMETA(DisplayName = "Small Grip Component"),
	ECT_M_GRIP UMETA(DisplayName = "Medium Grip Component"),
	ECT_L_GRIP UMETA(DisplayName = "Large Grip Component"),

	ECT_S_HANDLE UMETA(DisplayName = "Small Handle Component"),
	ECT_M_HANDLE UMETA(DisplayName = "Medium Handle Component"),
	ECT_L_HANDLE UMETA(DisplayName = "Large Handle Component"),

	ECT_BINDING UMETA(DisplayName = "Binding Component"),
	ECT_GUARD UMETA(DisplayName = "Gaurd Component"),
	ECT_SPIKE UMETA(DisplayName = "Spike Component")
};
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
	HT_MINING UMETA(DisplayName = "Mining"),
	HT_LOGGING UMETA(DisplayName = "Logging")
};

UENUM(BlueprintType, Meta = (Bitflags))
enum class EItemAction : uint8 {
	IA_NONE UMETA(DisplayName = "None"),
	IA_EQUIP UMETA(DisplayName = "Equip"),
	IA_UNEQUIP UMETA(DisplayName = "Unequip"),
	IA_DROP UMETA(DisplayName = "Drop"),
	IA_USE UMETA(DisplayName = "Use")
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
struct FExpRewardStruct {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESkillType Skill;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Exp = 0;
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
