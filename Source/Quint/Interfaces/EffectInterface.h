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
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnApply(AActor* ToActor);
	void OnApply_Implementation(AActor* ToActor) {}
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnRemove(AActor* FromActor);
	void OnRemove_Implementation(AActor* FromActor) {}

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool OnIncomingDamage(UPARAM(ref)FDamageStruct& Damage, UObject* DamageCauser, AController* CauserController = nullptr);
	virtual bool OnIncomingDamage_Implementation(UPARAM(ref)FDamageStruct& Damage, UObject* DamageCauser, AController* CauserController = nullptr) { return true; }

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool OnDamageTaken(UPARAM(ref)FDamageStruct& Damage, UObject* DamageCauser, AController* CauserController = nullptr);
	virtual bool OnDamageTaken_Implementation(UPARAM(ref)FDamageStruct& Damage, UObject* DamageCauser, AController* CauserController = nullptr) { return true; }

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool OnOutgoingDamage(UPARAM(ref)FDamageStruct& Damage, UObject* DamageTarget);
	virtual bool OnOutgoingDamage_Implementation(UPARAM(ref)FDamageStruct& Damage, UObject* DamageTarget) { return true; }

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool OnDamageDelt(UPARAM(ref)FDamageStruct& Damage, UObject* DamageTarget);
	virtual bool OnDamageDelt_Implementation(FDamageStruct& Damage, UObject* DamageTarget) { return true; }

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool OnActionSpeedCalculation(UPARAM(ref)float& Speed, EInteractionType Action);
	virtual bool OnActionSpeedCalculation_Implementation(UPARAM(ref)float& Speed, EInteractionType Action) { return true; }

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool OnActionCoolDownCalculation(UPARAM(ref)float& Speed, EInteractionType Action);
	virtual bool OnActionCoolDownCalculation_Implementation(UPARAM(ref)float& Duration, EInteractionType Action) { return true; }

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	int OnCalculateSkillLevel(ESkillType Skill, int Level);
	int OnCalculateSkillLevel_Implementation(ESkillType Skill, int Level) { return Level; }
};