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
class UEquipment;
UCLASS()
class QUINT_API UEquipmentComponent : public UItem {
	GENERATED_BODY()
protected:
	//TODO: Add Material Reference some how
	EEquipmentComponentType Type;
	//The set Level Required to craft with this
	//Using set levels so it does add X level per component
	TMap<ESkillType, int> CraftLevel;
	//The set level to use an item with this
	//Using set levels so it does add X level per component
	TMap<ESkillType, int> UseLevel;
	//The amount to modify the required craft level by
	TMap<ESkillType, int> CraftLevelModifier;
	//The amount to modify the required use level by
	TMap<ESkillType, int> UseLevelModifier;
	//How this component affects the color of the equipment
	FColor ColorModifier;
	int GetMapOfSkill(TMap<ESkillType, int> Map, ESkillType Type);
public:
	//When this item is used on something, like attack or mine
	virtual void OnUse(UObject* on);
	//When this item is constructed - may remove
	virtual void OnConstruct(UEquipment* Equipment);
	//When this component recives damage
	virtual void OnDamageComponent(int& Amount);
	int GetCraftLevelOf(ESkillType Skill) { return GetMapOfSkill(CraftLevel, Skill); };
	int GetUseLevel(ESkillType Skill) { return GetMapOfSkill(UseLevel, Skill); };
	int GetCraftLevelModifier(ESkillType Skill) { return GetMapOfSkill(CraftLevelModifier, Skill); };
	int GetUseLevelModifier(ESkillType Skill) { return GetMapOfSkill(UseLevelModifier, Skill); };
};
