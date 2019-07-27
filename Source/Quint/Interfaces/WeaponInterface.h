// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Engine/DataTable.h"
#include "Enumerations.h"
#include "WeaponInterface.generated.h"

/**
 * 
 */
class AAvatar;
UINTERFACE(MinimalAPI)
class  UWeaponInterface : public UInterface {
	GENERATED_BODY()
};

class QUINT_API IWeaponInterface {
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintNativeEvent)
	bool SetWeaponMode(int Mode = 0);
	bool SetWeaponMode_Implementation(int Mode = 0) { return false; };

	UFUNCTION(BlueprintNativeEvent)
	float GetWeaponRange();
	float GetWeaponRange_Implementation() { return 32.f; };

	UFUNCTION(BlueprintNativeEvent)
	float GetWeaponAttackDuration();
	float GetWeaponAttackDuration_Implementation() { return 0.25; };

	UFUNCTION(BlueprintNativeEvent)
	float GetWeaponAttackCooldown();
	float GetWeaponAttackCooldown_Implementation() { return 0.25; };

	UFUNCTION(BlueprintNativeEvent)
	void GetDamageStruct(FDamageStruct& Damage);
	void GetDamageStruct_Implementation(FDamageStruct& Damage) {};

	UFUNCTION(BlueprintNativeEvent)
	bool CanUseWeapon(AAvatar* Avatar);
	bool CanUseWeapon_Implementation(AAvatar* Avatar) { return true; };
	UFUNCTION(BlueprintNativeEvent)
	bool UseWeapon(AAvatar* DamageCauser, UPARAM(ref)FDamageStruct& Damage, AAvatar* DamageTarget);
	bool UseWeapon_Implementation(AAvatar* DamageCauser, UPARAM(ref)FDamageStruct& Damage, AAvatar* DamageTarget) { return CanUseWeapon(DamageCauser); };
};