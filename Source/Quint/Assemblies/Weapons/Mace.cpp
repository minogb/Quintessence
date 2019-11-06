// Fill out your copyright notice in the Description page of Project Settings.


#include "Mace.h"

#include "ConstructorHelpers.h"
#include "Interfaces/ComponentInterface.h"
#include "Json/Public/Serialization/JsonReader.h"
#include "Json/Public/Serialization/JsonSerializer.h"
#include "JsonUtilities/Public/JsonObjectConverter.h"

UMace::UMace() {
	//ImageTexture = CreateDefaultSubobject<UTexture2D>("Image");
	Actions = TArray<EItemAction>();
	ItemTableID = 14;
	MaxStackSize = 1;
}

FString UMace::GetSaveJSON()
{
	FString JSON;
	TSharedRef <TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&JSON);
	JsonWriter->WriteObjectStart();
	JsonWriter->WriteValue("UniqueID", UniqueItemId);
	JsonWriter->WriteValue("TableID", ItemTableID);
	if (HammerHead) {
		JsonWriter->WriteRawJSONValue("HammerHead", HammerHead->GetSaveJSON());

	}
	else {
		JsonWriter->WriteObjectStart("HammerHead");
		JsonWriter->WriteValue("UniqueID", 0);
		JsonWriter->WriteObjectEnd();
	}
	if (Spike) {
		JsonWriter->WriteRawJSONValue("Spike", Spike->GetSaveJSON());

	}
	else {
		JsonWriter->WriteObjectStart("Spike");
		JsonWriter->WriteValue("UniqueID", 0);
		JsonWriter->WriteObjectEnd();
	}
	if (ShortHandle) {
		JsonWriter->WriteRawJSONValue("ShortHandle", ShortHandle->GetSaveJSON());

	}
	else {
		JsonWriter->WriteObjectStart("ShortHandle");
		JsonWriter->WriteValue("UniqueID", 0);
		JsonWriter->WriteObjectEnd();
	}
	JsonWriter->WriteObjectEnd();
	JsonWriter->Close();
	return JSON;
}

UItem** UMace::GetComponent(EAssemblyComponentType Type){
	switch (Type) {
	case EAssemblyComponentType::ECT_HAMMER_HEAD:
		return &HammerHead;
	case EAssemblyComponentType::ECT_SPIKE:
		return &Spike;
	case EAssemblyComponentType::ECT_S_HANDLE:
		return &ShortHandle;
	}
	return nullptr;
}

void UMace::InitWithJson(TSharedPtr<FJsonObject> JsonData)
{
	if (JsonData) {
		if (JsonData->HasField("ID")) {
			UniqueItemId = JsonData->GetIntegerField("ID");
		}
		if (JsonData->HasField("HammerHead")) {
			TSharedPtr<FJsonObject> cData = JsonData->GetObjectField("HammerHead");
			if (cData->HasField("TableID")) {
				HammerHead = UItem::CreateItemFromTable(cData->GetIntegerField("TableID"), Owner, cData);
			}
		}
		if (JsonData->HasField("Spike")) {
			TSharedPtr<FJsonObject> cData = JsonData->GetObjectField("Spike");
			if (cData->HasField("TableID")) {
				Spike = UItem::CreateItemFromTable(cData->GetIntegerField("TableID"), Owner, cData);
			}
		}
		if (JsonData->HasField("ShortHandle")) {
			TSharedPtr<FJsonObject> cData = JsonData->GetObjectField("ShortHandle");
			if (cData->HasField("TableID")) {
				ShortHandle = UItem::CreateItemFromTable(cData->GetIntegerField("TableID"), Owner, cData);
			}
		}
	}
}

bool UMace::SetWeaponMode_Implementation(int Mode) {
	return false;
}

float UMace::GetWeaponRange_Implementation() {
	return 0.0f;
}

float UMace::GetWeaponAttackDuration_Implementation() {
	return 0.0f;
}

float UMace::GetWeaponAttackCooldown_Implementation() {
	return 0.0f;
}

bool UMace::GetDamageStruct_Implementation(UPARAM(ref)FDamageStruct & Damage) {
	return true;
}

bool UMace::CanUseWeapon_Implementation(AAvatar * Avatar) {
	return true;
}

bool UMace::UseWeapon_Implementation(AAvatar * DamageCauser, UPARAM(ref)FDamageStruct & Damage, AActor * DamageTarget) {

	return true;
}