// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "UObject/Interface.h"
#include "Interfaces/Equipment.h"
#include "Interfaces/EffectInterface.h"
#include "Enumerations.h"
#include "AssembledEquipment.generated.h"

UCLASS()
class QUINT_API UAssembledEquipment : public UItem, public IEquipmentInterface, public IEffectInterface {
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	virtual UItem* GetComponent(EAssemblyComponentType Type) { return nullptr; }

	UFUNCTION(BlueprintCallable)
	virtual TArray<UItem*> GetComponents() {return TArray<UItem*>();}

	UFUNCTION(BlueprintCallable)
	virtual bool SetComponent(UItem* Component) { return false; }

	UFUNCTION(BlueprintCallable)
	virtual bool SetComponents(TArray<UItem*>& Components);

	virtual TArray<FSkillLevelStruct> GetSkillsRequired_Implementation() override;

	virtual bool CanPlayerEquip_Implementation(AAvatar* Player) override;

	void OnApply_Implementation(AActor* ToActor) {}

	void OnRemove_Implementation(AActor* FromActor) {}

	virtual bool OnIncomingDamage_Implementation(UPARAM(ref)FDamageStruct& Damage, UObject* DamageCauser, AController* CauserController = nullptr) override;

	virtual bool OnDamageTaken_Implementation(UPARAM(ref)FDamageStruct& Damage, UObject* DamageCauser, AController* CauserController = nullptr) override;

	virtual bool OnOutgoingDamage_Implementation(UPARAM(ref)FDamageStruct& Damage, UObject* DamageTarget) override;

	virtual bool OnDamageDelt_Implementation(FDamageStruct& Damage, UObject* DamageTarget) override;

	virtual bool OnActionSpeedCalculation_Implementation(UPARAM(ref)float& Speed, EInteractionType Action) override;

	virtual bool OnActionCoolDownCalculation_Implementation(UPARAM(ref)float& Duration, EInteractionType Action) override;

	int OnCalculateSkillLevel_Implementation(ESkillType Skill, int Level) override;
};
