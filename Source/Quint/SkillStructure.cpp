// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillStructure.h"
#include "Json/Public/Dom/JsonObject.h"
#include "Json/Public/Serialization/JsonReader.h"
#include "Json/Public/Serialization/JsonSerializer.h"
#include "Engine/GameEngine.h"

void FPlayerSkilllLevelStruct::SetSkillAndExpLevel(ESkillType Skill, int Level, int CurrentExp){
	FLevelStruct* ref = GetSkill(Skill);
	if (ref) {
		ref->CurrentExp = CurrentExp;
		ref->Level = Level;
	}
}

int FPlayerSkilllLevelStruct::AddExp(ESkillType Skill, int Experience){
	FLevelStruct* ref = GetSkill(Skill);
	int leveldUpTo = 0;
	if (ref) {
		int NextLevelExp = FPlayerSkilllLevelStruct::GetExpRequiredForLevel(ref->Level + 1);
		ref->CurrentExp += Experience;
		while (NextLevelExp <= ref->CurrentExp) {
			ref->Level += 1;
			ref->CurrentExp = ref->CurrentExp - NextLevelExp;
			NextLevelExp = FPlayerSkilllLevelStruct::GetExpRequiredForLevel(ref->Level + 1);
		}
	}
	return leveldUpTo;
}

FLevelStruct* FPlayerSkilllLevelStruct::GetSkill(ESkillType Skill){
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
	case ESkillType::ST_SMITHINHG:
		reference = &Smithing;
		break;
	}
	return reference;
}
TArray<FLevelStruct> FPlayerSkilllLevelStruct::GetAsList()
{
	TArray<FLevelStruct> retVal = TArray<FLevelStruct>();
	retVal.Add(Logging);
	retVal.Add(Mining);
	retVal.Add(Fishing);
	retVal.Add(Farming);
	retVal.Add(Smithing);
	retVal.Add(Tailoring);
	retVal.Add(Woodworking);
	retVal.Add(Apothecary);
	retVal.Add(Ranged);
	retVal.Add(Magic);
	return TArray<FLevelStruct>();
}

int FPlayerSkilllLevelStruct::GetSkillLevel(ESkillType Skill){
	FLevelStruct* ref = GetSkill(Skill);
	if (ref) {
		return ref->Level;
	}
	return 1;
}

int FPlayerSkilllLevelStruct::GetSkillExp(ESkillType Skill){
	FLevelStruct* ref = GetSkill(Skill);
	if (ref) {
		return ref->CurrentExp;
	}
	return 0;
}

FString FPlayerSkilllLevelStruct::GetSaveJSON()
{
	FString JSON;
	TSharedRef <TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&JSON);

	JsonWriter->WriteObjectStart();

	JsonWriter->WriteObjectStart("Logging");
	JsonWriter->WriteValue("Level", Logging.Level);
	JsonWriter->WriteValue("CurrentExp", Logging.CurrentExp);
	JsonWriter->WriteObjectEnd();

	JsonWriter->WriteObjectStart("Mining");
	JsonWriter->WriteValue("Level", Mining.Level);
	JsonWriter->WriteValue("CurrentExp", Mining.CurrentExp);
	JsonWriter->WriteObjectEnd();

	JsonWriter->WriteObjectStart("Fishing");
	JsonWriter->WriteValue("Level", Fishing.Level);
	JsonWriter->WriteValue("CurrentExp", Fishing.CurrentExp);
	JsonWriter->WriteObjectEnd();

	JsonWriter->WriteObjectStart("Farming");
	JsonWriter->WriteValue("Level", Farming.Level);
	JsonWriter->WriteValue("CurrentExp", Farming.CurrentExp);
	JsonWriter->WriteObjectEnd();

	JsonWriter->WriteObjectStart("Smithing");
	JsonWriter->WriteValue("Level", Smithing.Level);
	JsonWriter->WriteValue("CurrentExp", Smithing.CurrentExp);
	JsonWriter->WriteObjectEnd();

	JsonWriter->WriteObjectStart("Tailoring");
	JsonWriter->WriteValue("Level", Tailoring.Level);
	JsonWriter->WriteValue("CurrentExp", Tailoring.CurrentExp);
	JsonWriter->WriteObjectEnd();

	JsonWriter->WriteObjectStart("Woodworking");
	JsonWriter->WriteValue("Level", Woodworking.Level);
	JsonWriter->WriteValue("CurrentExp", Woodworking.CurrentExp);
	JsonWriter->WriteObjectEnd();

	JsonWriter->WriteObjectStart("Apothecary");
	JsonWriter->WriteValue("Level", Apothecary.Level);
	JsonWriter->WriteValue("CurrentExp", Apothecary.CurrentExp);
	JsonWriter->WriteObjectEnd();

	JsonWriter->WriteObjectStart("Melee");
	JsonWriter->WriteValue("Level", Melee.Level);
	JsonWriter->WriteValue("CurrentExp", Melee.CurrentExp);
	JsonWriter->WriteObjectEnd();

	JsonWriter->WriteObjectStart("Ranged");
	JsonWriter->WriteValue("Level", Ranged.Level);
	JsonWriter->WriteValue("CurrentExp", Ranged.CurrentExp);
	JsonWriter->WriteObjectEnd();

	JsonWriter->WriteObjectStart("Magic");
	JsonWriter->WriteValue("Level", Magic.Level);
	JsonWriter->WriteValue("CurrentExp", Magic.CurrentExp);
	JsonWriter->WriteObjectEnd();

	JsonWriter->WriteObjectEnd();
	JsonWriter->Close();
	return JSON;
}

void FPlayerSkilllLevelStruct::InitWithJSON(TSharedPtr<FJsonObject> SkillJSON){
	if (SkillJSON->HasField("Logging")) {
		Logging.Level = SkillJSON->GetObjectField("Logging")->GetIntegerField("Level");
		Logging.CurrentExp = SkillJSON->GetObjectField("Logging")->GetIntegerField("Experience");
	}
	if (SkillJSON->HasField("Mining")) {
		Mining.Level = SkillJSON->GetObjectField("Mining")->GetIntegerField("Level");
		Mining.CurrentExp = SkillJSON->GetObjectField("Mining")->GetIntegerField("Experience");
	}
	if (SkillJSON->HasField("Fishing")) {
		Fishing.Level = SkillJSON->GetObjectField("Fishing")->GetIntegerField("Level");
		Fishing.CurrentExp = SkillJSON->GetObjectField("Fishing")->GetIntegerField("Experience");
	}
	if (SkillJSON->HasField("Smithing")) {
		Smithing.Level = SkillJSON->GetObjectField("Smithing")->GetIntegerField("Level");
		Smithing.CurrentExp = SkillJSON->GetObjectField("Smithing")->GetIntegerField("Experience");
	}
	if (SkillJSON->HasField("Tailoring")) {
		Tailoring.Level = SkillJSON->GetObjectField("Tailoring")->GetIntegerField("Level");
		Tailoring.CurrentExp = SkillJSON->GetObjectField("Tailoring")->GetIntegerField("Experience");
	}
	if (SkillJSON->HasField("Woodworking")) {
		Woodworking.Level = SkillJSON->GetObjectField("Woodworking")->GetIntegerField("Level");
		Woodworking.CurrentExp = SkillJSON->GetObjectField("Woodworking")->GetIntegerField("Experience");
	}
	if (SkillJSON->HasField("Apothecary")) {
		Apothecary.Level = SkillJSON->GetObjectField("Apothecary")->GetIntegerField("Level");
		Apothecary.CurrentExp = SkillJSON->GetObjectField("Apothecary")->GetIntegerField("Experience");
	}
	if (SkillJSON->HasField("Melee")) {
		Melee.Level = SkillJSON->GetObjectField("Melee")->GetIntegerField("Level");
		Melee.CurrentExp = SkillJSON->GetObjectField("Melee")->GetIntegerField("Experience");
	}
	if (SkillJSON->HasField("Ranged")) {
		Ranged.Level = SkillJSON->GetObjectField("Ranged")->GetIntegerField("Level");
		Ranged.CurrentExp = SkillJSON->GetObjectField("Ranged")->GetIntegerField("Experience");
	}
	if (SkillJSON->HasField("Magic")) {
		Magic.Level = SkillJSON->GetObjectField("Magic")->GetIntegerField("Level");
		Magic.CurrentExp = SkillJSON->GetObjectField("Magic")->GetIntegerField("Experience");
	}
}

int FPlayerSkilllLevelStruct::GetTotalExpRequiredForLevel(int Level){
	int total = 0;
	for (int i = 1; i < Level; i++) {
		total += FPlayerSkilllLevelStruct::GetExpRequiredForLevel(i);
	}
	return total;
}
