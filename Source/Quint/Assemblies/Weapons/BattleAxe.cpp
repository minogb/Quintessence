// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleAxe.h"

#include "ConstructorHelpers.h"
#include "Interfaces/ComponentInterface.h"
#include "Json/Public/Serialization/JsonReader.h"
#include "Json/Public/Serialization/JsonSerializer.h"
#include "JsonUtilities/Public/JsonObjectConverter.h"

UBattleAxe::UBattleAxe() {
	//ImageTexture = CreateDefaultSubobject<UTexture2D>("Image");
	Actions = TArray<EItemAction>();
	ItemTableID = 20;
	MaxStackSize = 1;
}

FString UBattleAxe::GetSaveJSON()
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
	if (Pommel) {
		JsonWriter->WriteRawJSONValue("Pommel", Pommel->GetSaveJSON());

	}
	else {
		JsonWriter->WriteObjectStart("Pommel");
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

UItem** UBattleAxe::GetComponent(EAssemblyComponentType Type){
	switch (Type) {
	case EAssemblyComponentType::ECT_AXE_HEAD:
		return &AxeHead;
	case EAssemblyComponentType::ECT_M_POMMEL:
		return &Pommel;
	case EAssemblyComponentType::ECT_M_GRIP:
		return &Grip;
	case EAssemblyComponentType::ECT_S_HANDLE:
		return &ShortHandle;
	}
	return nullptr;
}

void UBattleAxe::InitWithJson(TSharedPtr<FJsonObject> JsonData)
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
		if (JsonData->HasField("Pommel")) {
			TSharedPtr<FJsonObject> cData = JsonData->GetObjectField("Pommel");
			if (cData->HasField("TableID")) {
				Pommel = UItem::CreateItemFromTable(cData->GetIntegerField("TableID"), Owner, cData);
			}
		}
		if (JsonData->HasField("Grip")) {
			TSharedPtr<FJsonObject> cData = JsonData->GetObjectField("Grip");
			if (cData->HasField("TableID")) {
				Grip = UItem::CreateItemFromTable(cData->GetIntegerField("TableID"), Owner, cData);
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

bool UBattleAxe::SetWeaponMode_Implementation(int Mode) {
	return false;
}

float UBattleAxe::GetWeaponRange_Implementation() {
	return 0.0f;
}

float UBattleAxe::GetWeaponAttackDuration_Implementation() {
	return 0.0f;
}

float UBattleAxe::GetWeaponAttackCooldown_Implementation() {
	return 0.0f;
}

bool UBattleAxe::GetDamageStruct_Implementation(UPARAM(ref)FDamageStruct & Damage) {
	return true;
}

bool UBattleAxe::CanUseWeapon_Implementation(AAvatar * Avatar) {
	return true;
}

bool UBattleAxe::UseWeapon_Implementation(AAvatar * DamageCauser, UPARAM(ref)FDamageStruct & Damage, AActor * DamageTarget) {

	return true;
}
