// Fill out your copyright notice in the Description page of Project Settings.


#include "Mallet.h"
#include "ConstructorHelpers.h"
#include "Interfaces/ComponentInterface.h"
#include "Json/Public/Serialization/JsonReader.h"
#include "Json/Public/Serialization/JsonSerializer.h"
#include "JsonUtilities/Public/JsonObjectConverter.h"



UMallet::UMallet() {
	//ImageTexture = CreateDefaultSubobject<UTexture2D>("Image");
	Actions = TArray<EItemAction>();
	ItemTableID = 13;
	MaxStackSize = 1;
}

FString UMallet::GetSaveJSON()
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
	if (Binding) {
		JsonWriter->WriteRawJSONValue("Binding", Binding->GetSaveJSON());

	}
	else {
		JsonWriter->WriteObjectStart("Binding");
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

UItem** UMallet::GetComponent(EAssemblyComponentType Type) {
	switch (Type) {
	case EAssemblyComponentType::ECT_HAMMER_HEAD:
		return &HammerHead;
	case EAssemblyComponentType::ECT_BINDING:
		return &Binding;
	case EAssemblyComponentType::ECT_S_HANDLE:
		return &ShortHandle;
	}
	return nullptr;
}
void UMallet::InitWithJson(TSharedPtr<FJsonObject> JsonData)
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
		if (JsonData->HasField("Binding")) {
			TSharedPtr<FJsonObject> cData = JsonData->GetObjectField("Binding");
			if (cData->HasField("TableID")) {
				Binding = UItem::CreateItemFromTable(cData->GetIntegerField("TableID"), Owner, cData);
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
bool UMallet::SetWeaponMode_Implementation(int Mode) {
	return false;
}

float UMallet::GetWeaponRange_Implementation() {
	return 0.0f;
}

float UMallet::GetWeaponAttackDuration_Implementation() {
	return 0.0f;
}

float UMallet::GetWeaponAttackCooldown_Implementation() {
	return 0.0f;
}

bool UMallet::GetDamageStruct_Implementation(UPARAM(ref)FDamageStruct & Damage) {
	return true;
}

bool UMallet::CanUseWeapon_Implementation(AAvatar * Avatar) {
	return true;
}

bool UMallet::UseWeapon_Implementation(AAvatar * DamageCauser, UPARAM(ref)FDamageStruct & Damage, AActor * DamageTarget) {

	return true;
}
