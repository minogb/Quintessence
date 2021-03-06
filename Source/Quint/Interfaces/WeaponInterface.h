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

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool SetWeaponMode(int Mode = 0);
	virtual bool SetWeaponMode_Implementation(int Mode = 0) { return false; };

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	float GetWeaponRange();
	virtual float GetWeaponRange_Implementation() { return 32.f; };

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	float GetWeaponAttackDuration();
	virtual float GetWeaponAttackDuration_Implementation() { return 0.25; };

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	float GetWeaponAttackCooldown();
	virtual float GetWeaponAttackCooldown_Implementation() { return 0.25; };

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool GetDamageStruct(UPARAM(ref)FDamageStruct& Damage);
	virtual bool GetDamageStruct_Implementation(UPARAM(ref)FDamageStruct& Damage) { return true; };

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool CanUseWeapon(AAvatar* Avatar);
	virtual bool CanUseWeapon_Implementation(AAvatar* Avatar) { return true; };

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool UseWeapon(AAvatar* DamageCauser, UPARAM(ref)FDamageStruct& Damage, AActor* DamageTarget);
	virtual bool UseWeapon_Implementation(AAvatar* DamageCauser, UPARAM(ref)FDamageStruct& Damage, AActor* DamageTarget) { return CanUseWeapon(DamageCauser); };
};