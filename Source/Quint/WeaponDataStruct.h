// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "Engine/DataTable.h"
#include "Components/SkeletalMeshComponent.h"
#include "QuintDamageType.h"
#include "WeaponDataStruct.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum EWeaponScaleEnum {
	S_Scale UMETA(DisplayName = "S"), //120
	A_Scale UMETA(DisplayName = "A"), //100
	B_Scale UMETA(DisplayName = "B"), // 75
	C_Scale UMETA(DisplayName = "C"), // 50
	D_Scale UMETA(DisplayName = "D"), // 25
	F_Scale UMETA(DisplayName = "F")  //  0
};

UENUM(BlueprintType)
enum EWeaponHandEnum {
	Primary_Hand UMETA(DisplayName = "Primary Hand"),
	Off_Hand UMETA(DisplayName = "Off Hand"),
	Dual_Hand UMETA(DisplayName = "Dual Hand")
};


USTRUCT(Blueprintable)
struct QUINT_API FWeaponDataStruct : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USkeletalMesh* WeaponMesh = nullptr;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TArray<UAnimMontage*> AttackAnimations;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TArray<UAnimMontage*> BlockAnimations;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int32 BaseDamage = 0;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float WeaponSpeed = 1;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float WeaponRange = 0;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TEnumAsByte<EWeaponHandEnum> WeaponHand = Primary_Hand;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TEnumAsByte<EWeaponScaleEnum> AgilityScale = A_Scale;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TEnumAsByte<EWeaponScaleEnum> StregnthScale = A_Scale;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TEnumAsByte<EWeaponScaleEnum> DexterityScale = A_Scale;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TSubclassOf<UQuintDamageType> DamageType = UQuintDamageType::StaticClass();
};
