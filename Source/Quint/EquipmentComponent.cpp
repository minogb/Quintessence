// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentComponent.h"


void UEquipmentComponent::OnUse_Implementation(UObject * on)
{
}

void UEquipmentComponent::OnConstruct_Implementation(UEquipment * Equipment)
{
}

void UEquipmentComponent::OnDamageComponent_Implementation(int & Amount)
{
}

int UEquipmentComponent::GetMapOfSkill(TMap<ESkillType, int> Map, ESkillType SkillType) {
	if (Map.Contains(SkillType))
		return Map[SkillType];
	return 0;
}