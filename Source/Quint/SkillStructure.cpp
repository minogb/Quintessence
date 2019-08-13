// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillStructure.h"

void FPlayerSkilllLevelStruct::SetSkillAndExpLevel(ESkillType Skill, int Level, int CurrentExp){
	FLevelStruct* ref = GetSkill(Skill);
	if (ref) {
		ref->CurrentExp = CurrentExp;
		ref->Level = Level;
	}
}

void FPlayerSkilllLevelStruct::AddExp(ESkillType Skill, int Experience){
	FLevelStruct* ref = GetSkill(Skill);
	if (ref) {
		ref->CurrentExp += Experience;
	}
}

FLevelStruct* FPlayerSkilllLevelStruct::GetSkill(ESkillType Skill)
{
	FLevelStruct* reference = nullptr;
	switch (Skill) {
	case ESkillType::ST_LOGGING:
		reference = &Logging;
		break;
	case ESkillType::ST_MINING:
		reference = &Mining;
		break;
	case ESkillType::ST_FISHING:
		reference = &Fishing;
		break;
	case ESkillType::ST_FARMING:
		reference = &Farming;
		break;
	case ESkillType::ST_TAILORING:
		reference = &Tailoring;
		break;
	case ESkillType::ST_APOTHECARY:
		reference = &Apothecary;
		break;
	case ESkillType::ST_MELEE:
		reference = &Melee;
		break;
	case ESkillType::ST_RANGED:
		reference = &Ranged;
		break;
	case ESkillType::ST_MAGIC:
		reference = &Magic;
		break;
	case ESkillType::ST_WOODWORKING:
		reference = &Woodworking;
		break;
	}
	return reference;
}

int FPlayerSkilllLevelStruct::GetSkillLevel(ESkillType Skill)
{
	FLevelStruct* ref = GetSkill(Skill);
	if (ref) {
		return ref->Level;
	}
	return 1;
}

int FPlayerSkilllLevelStruct::GetSkillExp(ESkillType Skill)
{
	FLevelStruct* ref = GetSkill(Skill);
	if (ref) {
		return ref->CurrentExp;
	}
	return 0;
}
