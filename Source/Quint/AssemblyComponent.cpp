// Fill out your copyright notice in the Description page of Project Settings.


#include "AssemblyComponent.h"


void UAssemblyComponent::OnUse_Implementation(UObject * on)
{
}

void UAssemblyComponent::OnConstruct_Implementation(UObject * Equipment)
{
}

void UAssemblyComponent::OnDamageComponent_Implementation(int & Amount)
{
}

int UAssemblyComponent::GetMapOfSkill(TMap<ESkillType, int> Map, ESkillType SkillType) {
	if (Map.Contains(SkillType))
		return Map[SkillType];
	return 0;
}