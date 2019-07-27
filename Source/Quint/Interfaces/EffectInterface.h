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
	bool OnIncomingDamage(UPARAM(ref)FDamageStruct& Damage, UObject* DamageCauser, AController* CauserController = nullptr);
	virtual bool OnIncomingDamage_Implementation(UPARAM(ref)FDamageStruct& Damage, UObject* DamageCauser, AController* CauserController = nullptr) { return true; }
	
	UFUNCTION(BlueprintNativeEvent)
	bool OnDamageTaken(UPARAM(ref)FDamageStruct& Damage, UObject* DamageCauser, AController* CauserController = nullptr);
	virtual bool OnDamageTaken_Implementation(UPARAM(ref)FDamageStruct& Damage, UObject* DamageCauser, AController* CauserController = nullptr) { return true; }

	UFUNCTION(BlueprintNativeEvent)
	bool OnOutgoingDamage(UPARAM(ref)FDamageStruct& Damage, UObject* DamageTarget);
	virtual bool OnOutgoingDamage_Implementation(UPARAM(ref)FDamageStruct& Damage, UObject* DamageTarget) { return true; }

	UFUNCTION(BlueprintNativeEvent)
	bool OnDamageDelt(UPARAM(ref)FDamageStruct& Damage, UObject* DamageTarget);
	virtual bool OnDamageDelt_Implementation(FDamageStruct& Damage, UObject* DamageTarget) { return true; }

	UFUNCTION(BlueprintNativeEvent)
	bool OnActionSpeedCalculation(UPARAM(ref)float& Speed, EInteractionType Action);
	virtual bool OnActionSpeedCalculation_Implementation(UPARAM(ref)float& Speed, EInteractionType Action) { return true; }

	UFUNCTION(BlueprintNativeEvent)
	bool OnActionCoolDownCalculation(UPARAM(ref)float& Speed, EInteractionType Action);
	virtual bool OnActionCoolDownCalculation_Implementation(UPARAM(ref)float& Duration, EInteractionType Action) { return true; }
};