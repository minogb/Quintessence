// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SkillStructure.generated.h"
/*
This is a work around because TMaps do not get replicated
*/
UENUM(BlueprintType, Meta = (Bitflags))
enum class ESkillType : uint8 {
	ST_NONE UMETA(DisplayName = "None"),

	//Gathering Skills
	ST_LOGGING UMETA(DisplayName = "Logging"),
	ST_MINING UMETA(DisplayName = "Mining"),
	ST_FISHING UMETA(DisplayName = "Fishing"),
	ST_FARMING UMETA(DisplayName = "Farming"),

	//Refining Skills
	ST_SMITHINHG UMETA(DisplayName = "Smithing"),
	ST_TAILORING UMETA(DisplayName = "Tailoring"),
	ST_APOTHECARY UMETA(DisplayName = "Apothecary"),
	ST_WOODWORKING UMETA(DisplayName = "Woodworking"),
	
	//Combat Skills
	ST_MELEE UMETA(DisplayName = "Melee"),
	ST_RANGED UMETA(DisplayName = "Ranged"),
	ST_MAGIC UMETA(DisplayName = "Magic")
};

USTRUCT(BlueprintType)
struct FSkillLevelStruct {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESkillType Skill = ESkillType::ST_NONE;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Level = 1;
};
USTRUCT(BlueprintType)
struct FLevelStruct {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int Level = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurrentExp;
};

USTRUCT(BlueprintType)
struct FPlayerSkilllLevelStruct {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLevelStruct Logging;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLevelStruct Mining;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLevelStruct Fishing;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLevelStruct Farming;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLevelStruct Smithing;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLevelStruct Tailoring;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLevelStruct Woodworking;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLevelStruct Apothecary;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLevelStruct Melee;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLevelStruct Ranged;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLevelStruct Magic;
	
	void SetSkillAndExpLevel(ESkillType Skill, int Level, int CurrentExp);
	int AddExp(ESkillType Skill, int Experience);
	FLevelStruct* GetSkill(ESkillType Skill);
	TArray<FLevelStruct> GetAsList();
	int GetSkillLevel(ESkillType Skill);
	int GetSkillExp(ESkillType Skill);
	FString GetSaveJSON();
	void InitWithJSON(TSharedPtr<FJsonObject> InventoryJSON);
	static int GetExpRequiredForLevel(int Level) { return 3.14159265359 * 10 * FMath::Pow(2, (float)Level / (3.14159265359 * 2)); }
	static int GetTotalExpRequiredForLevel(int Level);
};
