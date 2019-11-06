// Fill out your copyright notice in the Description page of Project Settings.


#include "PoleAxe.h"
#include "ConstructorHelpers.h"
#include "Interfaces/ComponentInterface.h"
#include "Json/Public/Serialization/JsonReader.h"
#include "Json/Public/Serialization/JsonSerializer.h"
#include "JsonUtilities/Public/JsonObjectConverter.h"

UPoleAxe::UPoleAxe() {
	//ImageTexture = CreateDefaultSubobject<UTexture2D>("Image");
	Actions = TArray<EItemAction>();
	ItemTableID = 11;
	MaxStackSize = 1;
}

FString UPoleAxe::GetSaveJSON()
{
	FString JSON;
	TSharedRef <TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&JSON);
	JsonWriter->WriteObjectStart();
	JsonWriter->WriteValue("UniqueID", UniqueItemId);
	JsonWriter->WriteValue("TableID", ItemTableID);
	if (AxeHead) {
		JsonWriter->WriteRawJSONValue("AxeHead", AxeHead->GetSaveJSON());

	}
	else {
		JsonWriter->WriteObjectStart("AxeHead");
		JsonWriter->WriteValue("UniqueID", 0);
		JsonWriter->WriteObjectEnd();
	}
	if (HammerHead) {
		JsonWriter->WriteRawJSONValue("HammerHead", HammerHead->GetSaveJSON());

	}
	else {
		JsonWriter->WriteObjectStart("HammerHead");
		JsonWriter->WriteValue("UniqueID", 0);
		JsonWriter->WriteObjectEnd();
	}
	if (LongGrip) {
		JsonWriter->WriteRawJSONValue("LongGrip", LongGrip->GetSaveJSON());

	}
	else {
		JsonWriter->WriteObjectStart("LongGrip");
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

UItem** UPoleAxe::GetComponent(EAssemblyComponentType Type){
	switch (Type) {
	case EAssemblyComponentType::ECT_AXE_HEAD:
		return &AxeHead;
	case EAssemblyComponentType::ECT_HAMMER_HEAD:
		return &HammerHead;
	case EAssemblyComponentType::ECT_L_GRIP:
		return &LongGrip;
	case EAssemblyComponentType::ECT_L_HANDLE:
		return &LongHandle;
	}
	return nullptr;
}

void UPoleAxe::InitWithJson(TSharedPtr<FJsonObject> JsonData)
{
	if (JsonData) {
		if (JsonData->HasField("ID")) {
			UniqueItemId = JsonData->GetIntegerField("ID");
		}
		if (JsonData->HasField("AxeHead")) {
			TSharedPtr<FJsonObject> cData = JsonData->GetObjectField("AxeHead");
			if (cData->HasField("TableID")) {
				AxeHead = UItem::CreateItemFromTable(cData->GetIntegerField("TableID"), Owner, cData);
			}
		}
		if (JsonData->HasField("HammerHead")) {
			TSharedPtr<FJsonObject> cData = JsonData->GetObjectField("HammerHead");
			if (cData->HasField("TableID")) {
				HammerHead = UItem::CreateItemFromTable(cData->GetIntegerField("TableID"), Owner, cData);
			}
		}
		if (JsonData->HasField("LongGrip")) {
			TSharedPtr<FJsonObject> cData = JsonData->GetObjectField("LongGrip");
			if (cData->HasField("TableID")) {
				LongGrip = UItem::CreateItemFromTable(cData->GetIntegerField("TableID"), Owner, cData);
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


bool UPoleAxe::SetWeaponMode_Implementation(int Mode) {
	return false;
}

float UPoleAxe::GetWeaponRange_Implementation() {
	return 0.0f;
}

float UPoleAxe::GetWeaponAttackDuration_Implementation() {
	return 0.0f;
}

float UPoleAxe::GetWeaponAttackCooldown_Implementation() {
	return 0.0f;
}

bool UPoleAxe::GetDamageStruct_Implementation(UPARAM(ref)FDamageStruct & Damage) {
	return true;
}

bool UPoleAxe::CanUseWeapon_Implementation(AAvatar * Avatar) {
	return true;
}

bool UPoleAxe::UseWeapon_Implementation(AAvatar * DamageCauser, UPARAM(ref)FDamageStruct & Damage, AActor * DamageTarget) {

	return true;
}