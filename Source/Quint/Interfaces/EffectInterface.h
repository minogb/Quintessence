// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Enumerations.h"
#include "EffectInterface.generated.h"

/**
 * 
 */

UINTERFACE(MinimalAPI)
class  UEffectInterface : public UInterface {
	GENERATED_BODY()
};

class QUINT_API IEffectInterface {
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent)
	void OnApply(AActor* ToActor);
	void OnApply_Implementation(AActor* ToActor) {}
	UFUNCTION(BlueprintNativeEvent)
	void OnRemove(AActor* FromActor);
	void OnRemove_Implementation(AActor* FromActor) {}

	UFUNCTION(BlueprintNativeEvent)
	void OnIncomingDamage(FDamageStruct& Damage, UObject* DamageCauser, AController* CauserController = nullptr);
	virtual void OnIncomingDamage_Implementation(FDamageStruct& Damage, UObject* DamageCauser, AController* CauserController = nullptr) {}
	
	UFUNCTION(BlueprintNativeEvent)
	void OnDamageTaken(FDamageStruct& Damage, UObject* DamageCauser, AController* CauserController = nullptr);
	virtual void OnDamageTaken_Implementation(FDamageStruct& Damage, UObject* DamageCauser, AController* CauserController = nullptr) {}

	UFUNCTION(BlueprintNativeEvent)
	void OnOutgoingDamage(FDamageStruct& Damage, UObject* DamageTarget);
	virtual void OnOutgoingDamage_Implementation(FDamageStruct& Damage, UObject* DamageTarget) {}

	UFUNCTION(BlueprintNativeEvent)
	void OnDamageDelt(FDamageStruct& Damage, UObject* DamageTarget);
	virtual void OnDamageDelt_Implementation(FDamageStruct& Damage, UObject* DamageTarget) {}

	UFUNCTION(BlueprintNativeEvent)
	void OnActionSpeedCalculation(float& Speed, EInteractionType Action);
	virtual void OnActionSpeedCalculation_Implementation(float& Speed, EInteractionType Action) {}

	UFUNCTION(BlueprintNativeEvent)
	void OnActionCoolDownCalculation(float& Speed, EInteractionType Action);
	virtual void OnActionCoolDownCalculation_Implementation(float& Duration, EInteractionType Action) {}
};