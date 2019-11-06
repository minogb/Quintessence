// Fill out your copyright notice in the Description page of Project Settings.


#include "LongAxe.h"

#include "ConstructorHelpers.h"
#include "Interfaces/ComponentInterface.h"
#include "Json/Public/Serialization/JsonReader.h"
#include "Json/Public/Serialization/JsonSerializer.h"
#include "JsonUtilities/Public/JsonObjectConverter.h"

ULongAxe::ULongAxe() {
	//ImageTexture = CreateDefaultSubobject<UTexture2D>("Image");
	Actions = TArray<EItemAction>();
	ItemTableID = 16;
	MaxStackSize = 1;
}

FString ULongAxe::GetSaveJSON()
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

UItem** ULongAxe::GetComponent(EAssemblyComponentType Type){
	switch (Type) {
	case EAssemblyComponentType::ECT_AXE_HEAD:
		return &AxeHead;
	case EAssemblyComponentType::ECT_L_HANDLE:
		return &LongHandle;
	}
	return nullptr;
}

void ULongAxe::InitWithJson(TSharedPtr<FJsonObject> JsonData)
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
		if (JsonData->HasField("LongHandle")) {
			TSharedPtr<FJsonObject> cData = JsonData->GetObjectField("LongHandle");
			if (cData->HasField("TableID")) {
				LongHandle = UItem::CreateItemFromTable(cData->GetIntegerField("TableID"), Owner, cData);
			}
		}
	}
}

bool ULongAxe::SetWeaponMode_Implementation(int Mode) {
	return false;
}

float ULongAxe::GetWeaponRange_Implementation() {
	return 0.0f;
}

float ULongAxe::GetWeaponAttackDuration_Implementation() {
	return 0.0f;
}

float ULongAxe::GetWeaponAttackCooldown_Implementation() {
	return 0.0f;
}

bool ULongAxe::GetDamageStruct_Implementation(UPARAM(ref)FDamageStruct & Damage) {
	return true;
}

bool ULongAxe::CanUseWeapon_Implementation(AAvatar * Avatar) {
	return true;
}

bool ULongAxe::UseWeapon_Implementation(AAvatar * DamageCauser, UPARAM(ref)FDamageStruct & Damage, AActor * DamageTarget) {

	return true;
}