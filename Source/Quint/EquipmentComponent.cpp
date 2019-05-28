// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentComponent.h"


void UEquipmentComponent::OnUse(UObject * on)
{
}

void UEquipmentComponent::OnConstruct(UEquipment * Equipment)
{
}

void UEquipmentComponent::OnDamageComponent(int & Amount)
{
}

int UEquipmentComponent::GetMapOfSkill(TMap<ESkillType, int> Map, ESkillType Type) {
	if (Map.Contains(Type))
		return Map[Type];
	return 0;
}