// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WeaponDataStruct.h"
#include "WeaponHelper.generated.h"

/**
 * 
 */
class UQuintDamageType;
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
	static int GetWeaponDamageForPlayById(int id, int playerId);
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static float GetPercentFromScale(TEnumAsByte<EWeaponScaleEnum> scale, int playerScaleLevel);
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static TSubclassOf<UQuintDamageType> GetWeaponDamageType(int id);
	
};
