// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "ComponentStructure.h"
#include "Enumerations.h"
#include "EquipmentComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class QUINT_API UEquipmentComponent : public UItem {
	GENERATED_BODY()
protected:
	//TODO: Add Material Reference some how
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setup", meta = (AllowPrivateAccess = "true"))
	EEquipmentComponentType ComponentType;
	//The set Level Required to craft with this
	//Using set levels so it does add X level per component
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setup", meta = (AllowPrivateAccess = "true"))
	TMap<ESkillType, int> CraftLevel;
	//The set level to use an item with this
	//Using set levels so it does add X level per component
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setup", meta = (AllowPrivateAccess = "true"))
	TMap<ESkillType, int> UseLevel;
	//The amount to modify the required craft level by
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setup", meta = (AllowPrivateAccess = "true"))
	TMap<ESkillType, int> CraftLevelModifier;
	//The amount to modify the required use level by
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setup", meta = (AllowPrivateAccess = "true"))
	TMap<ESkillType, int> UseLevelModifier;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Info", meta = (AllowPrivateAccess = "true"))
	TMap<EHarvestType, int> HarvestLevels;
	//How this component affects the color of the equipment
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setup", meta = (AllowPrivateAccess = "true"))
	FColor ColorModifier;
	int GetMapOfSkill(TMap<ESkillType, int> Map, ESkillType SkillType);
public:
	//When this item is used on something, like attack or mine
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnUse(UObject* on);
	virtual void OnUse_Implementation(UObject* on);
	//When this item is constructed - may remove
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnConstruct(UObject* Equipment);
	virtual void OnConstruct_Implementation(UObject* Equipment);
	//When this component recives damage _Implementation
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnDamageComponent(int& Amount);
	virtual void OnDamageComponent_Implementation(int& Amount);
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetCraftLevelOf(ESkillType Skill) { return GetMapOfSkill(CraftLevel, Skill); };
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetUseLevel(ESkillType Skill) { return GetMapOfSkill(UseLevel, Skill); };
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetCraftLevelModifier(ESkillType Skill) { return GetMapOfSkill(CraftLevelModifier, Skill); };
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetUseLevelModifier(ESkillType Skill) { return GetMapOfSkill(UseLevelModifier, Skill); };
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetHarvestLevel(EHarvestType Type) { return HarvestLevels.Contains(Type) ? HarvestLevels[Type] : 0; };
	UFUNCTION(BlueprintCallable, BlueprintPure)
	EEquipmentComponentType GetComponentType() { return ComponentType; };
};
