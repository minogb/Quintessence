// Fill out your copyright notice in the Description page of Project Settings.


#include "Warhammer.h"

#include "ConstructorHelpers.h"
#include "Interfaces/ComponentInterface.h"
#include "Json/Public/Serialization/JsonReader.h"
#include "Json/Public/Serialization/JsonSerializer.h"
#include "JsonUtilities/Public/JsonObjectConverter.h"


UWarhammer::UWarhammer() {
	//ImageTexture = CreateDefaultSubobject<UTexture2D>("Image");
	Actions = TArray<EItemAction>();
	ItemTableID = 8;
	MaxStackSize = 1;
}

FString UWarhammer::GetSaveJSON()
{
	FString JSON;
	TSharedRef <TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&JSON);
	JsonWriter->WriteObjectStart();
	JsonWriter->WriteValue("UniqueID", UniqueItemId);
	JsonWriter->WriteValue("TableID", ItemTableID);
	if (LargeHammerHead) {
		JsonWriter->WriteRawJSONValue("LargeHammerHead", LargeHammerHead->GetSaveJSON());

	}
	else {
		JsonWriter->WriteObjectStart("LargeHammerHead");
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
	if (Grip) {
		JsonWriter->WriteRawJSONValue("Grip", Grip->GetSaveJSON());

	}
	else {
		JsonWriter->WriteObjectStart("Grip");
		JsonWriter->WriteValue("UniqueID", 0);
		JsonWriter->WriteObjectEnd();
	}
	if (LongHandle) {
		JsonWriter->WriteRawJSONValue("LongHandle", LongHandle->GetSaveJSON());

	}
	else {
		JsonWriter->WriteObjectStart("LongHandle");
		JsonWriter->WriteValue("UniqueID", 0);
		JsonWriter->WriteObjectEnd();
	}
	JsonWriter->WriteObjectEnd();
	JsonWriter->Close();
	return JSON;
}

void UWarhammer::InitWithJson(TSharedPtr<FJsonObject> JsonData){
	if (JsonData) {
		if (JsonData->HasField("ID")) {
			UniqueItemId = JsonData->GetIntegerField("ID");
		}
		if (JsonData->HasField("LargeHammerHead")) {
			TSharedPtr<FJsonObject> cData = JsonData->GetObjectField("LargeHammerHead");
			if (cData->HasField("TableID")) {
				LargeHammerHead = UItem::CreateItemFromTable(cData->GetIntegerField("TableID"), Owner, cData);
			}
		}
		if (JsonData->HasField("Spike")) {
			TSharedPtr<FJsonObject> cData = JsonData->GetObjectField("Spike");
			if (cData->HasField("TableID")) {
				Spike = UItem::CreateItemFromTable(cData->GetIntegerField("TableID"), Owner, cData);
			}
		}
		if (JsonData->HasField("Grip")) {
			TSharedPtr<FJsonObject> cData = JsonData->GetObjectField("Grip");
			if (cData->HasField("TableID")) {
				Grip = UItem::CreateItemFromTable(cData->GetIntegerField("TableID"), Owner, cData);
			}
		}
		if (JsonData->HasField("LongHandle")) {
			TSharedPtr<FJsonObject> cData = JsonData->GetObjectField("LongHandle");
			if (cData->HasField("TableID")) {
				LongHandle = UItem::CreateItemFromTable(cData->GetIntegerField("TableID"), Owner, cData);
			}
		}
	}
}

UItem** UWarhammer::GetComponent(EAssemblyComponentType Type){
	switch (Type) {
	case EAssemblyComponentType::ECT_L_HAMMER_HEAD:
	return &LargeHammerHead;
	case EAssemblyComponentType::ECT_SPIKE:
	return &Spike;
	case EAssemblyComponentType::ECT_M_GRIP:
	return &Grip;
	case EAssemblyComponentType::ECT_L_HANDLE:
	return &LongHandle;
	}
	return nullptr;
}


bool UWarhammer::SetWeaponMode_Implementation(int Mode) {
	return false;
}

float UWarhammer::GetWeaponRange_Implementation() {
	return 0.0f;
}

float UWarhammer::GetWeaponAttackDuration_Implementation() {
	return 0.0f;
}

float UWarhammer::GetWeaponAttackCooldown_Implementation() {
	return 0.0f;
}

bool UWarhammer::GetDamageStruct_Implementation(UPARAM(ref)FDamageStruct & Damage) {
	return true;
}

bool UWarhammer::CanUseWeapon_Implementation(AAvatar * Avatar) {
	return true;
}

bool UWarhammer::UseWeapon_Implementation(AAvatar * DamageCauser, UPARAM(ref)FDamageStruct & Damage, AActor * DamageTarget) {

	return true;
}