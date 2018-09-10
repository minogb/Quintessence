// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WeaponDataStruct.h"
#include "WeaponHelper.generated.h"

/**
 * 
 */
static UDataTable* WeaponLookupTable = nullptr;
static const FString WEAPON_CONTEXT_STRING(TEXT("GENERAL"));
UCLASS()
class QUINT_API UWeaponHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
protected:
public:
	UWeaponHelper();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static bool GetWeaponStructFromId(int id, FWeaponDataStruct& weaponStruct);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static bool GetWeaponOrDefault(int id, FWeaponDataStruct& weaponStruct);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static bool GetWeaponDamageForPlayById(int id, int playerId, int& damage);
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static float GetPercentFromScale(TEnumAsByte<EWeaponScaleEnum> scale, int playerScaleLevel);
	
};
