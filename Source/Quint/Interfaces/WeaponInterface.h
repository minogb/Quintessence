// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WeaponInterface.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI)
class  UWeaponInterface : public UInterface {
	GENERATED_BODY()
};

class QUINT_API IWeaponInterface {
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintNativeEvent)
	float GetWeaponRange();
	float GetWeaponRange_Implementation() { return 32.f; };

	UFUNCTION(BlueprintNativeEvent)
	float GetWeaponAttackDuration();
	float GetWeaponAttackDuration_Implementation() { return 0.25; };

	UFUNCTION(BlueprintNativeEvent)
	float GetWeaponAttackCooldown();
	float GetWeaponAttackCooldown_Implementation() { return 0.25; };
};