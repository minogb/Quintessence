// Fill out your copyright notice in the Description page of Project Settings.


#include "BroadSword.h"
#include "ConstructorHelpers.h"
#include "Interfaces/ComponentInterface.h"
#include "Json/Public/Serialization/JsonReader.h"
#include "Json/Public/Serialization/JsonSerializer.h"
#include "JsonUtilities/Public/JsonObjectConverter.h"


UBroadSword::UBroadSword() {
	//ImageTexture = CreateDefaultSubobject<UTexture2D>("Image");
	Actions = TArray<EItemAction>();
	ItemTableID = 19;
	MaxStackSize = 1;
}

FString UBroadSword::GetSaveJSON()
{
	FString JSON;
	TSharedRef <TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&JSON);
	JsonWriter->WriteObjectStart();
	JsonWriter->WriteValue("UniqueID", UniqueItemId);
	JsonWriter->WriteValue("TableID", ItemTableID);
	if (HeavyBlade) {
		JsonWriter->WriteRawJSONValue("HeavyBlade", HeavyBlade->GetSaveJSON());

	}
	else {
		JsonWriter->WriteObjectStart("HeavyBlade");
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
	if (LongGrip) {
		JsonWriter->WriteRawJSONValue("LongGrip", LongGrip->GetSaveJSON());

	}
	else {
		JsonWriter->WriteObjectStart("LongGrip");
		JsonWriter->WriteValue("UniqueID", 0);
		JsonWriter->WriteObjectEnd();
	}
	if (Guard) {
		JsonWriter->WriteRawJSONValue("Guard", Guard->GetSaveJSON());

	}
	else {
		JsonWriter->WriteObjectStart("Guard");
		JsonWriter->WriteValue("UniqueID", 0);
		JsonWriter->WriteObjectEnd();
	}
	JsonWriter->WriteObjectEnd();
	JsonWriter->Close();
	return JSON;
}

UItem** UBroadSword::GetComponent(EAssemblyComponentType Type){
	switch (Type) {
	case EAssemblyComponentType::ECT_H_BLADE:
		return &HeavyBlade;
	case EAssemblyComponentType::ECT_M_POMMEL:
		return &Pommel;
	case EAssemblyComponentType::ECT_L_GRIP:
		return &LongGrip;
	case EAssemblyComponentType::ECT_GUARD:
		return &Guard;
	}
	return nullptr;
}

void UBroadSword::InitWithJson(TSharedPtr<FJsonObject> JsonData)
{
	if (JsonData) {
		if (JsonData->HasField("ID")) {
			UniqueItemId = JsonData->GetIntegerField("ID");
		}
		if (JsonData->HasField("HeavyBlade")) {
			TSharedPtr<FJsonObject> cData = JsonData->GetObjectField("HeavyBlade");
			if (cData->HasField("TableID")) {
				HeavyBlade = UItem::CreateItemFromTable(cData->GetIntegerField("TableID"), Owner, cData);
			}
		}
		if (JsonData->HasField("Pommel")) {
			TSharedPtr<FJsonObject> cData = JsonData->GetObjectField("Pommel");
			if (cData->HasField("TableID")) {
				Pommel = UItem::CreateItemFromTable(cData->GetIntegerField("TableID"), Owner, cData);
			}
		}
		if (JsonData->HasField("LongGrip")) {
			TSharedPtr<FJsonObject> cData = JsonData->GetObjectField("LongGrip");
			if (cData->HasField("TableID")) {
				LongGrip = UItem::CreateItemFromTable(cData->GetIntegerField("TableID"), Owner, cData);
			}
		}
		if (JsonData->HasField("Guard")) {
			TSharedPtr<FJsonObject> cData = JsonData->GetObjectField("Guard");
			if (cData->HasField("TableID")) {
				Guard = UItem::CreateItemFromTable(cData->GetIntegerField("TableID"), Owner, cData);
			}
		}
	}
}

bool UBroadSword::SetWeaponMode_Implementation(int Mode) {
	return false;
}

float UBroadSword::GetWeaponRange_Implementation() {
	return 0.0f;
}

float UBroadSword::GetWeaponAttackDuration_Implementation() {
	return 0.0f;
}

float UBroadSword::GetWeaponAttackCooldown_Implementation() {
	return 0.0f;
}

bool UBroadSword::GetDamageStruct_Implementation(UPARAM(ref)FDamageStruct & Damage) {
	return true;
}

bool UBroadSword::CanUseWeapon_Implementation(AAvatar * Avatar) {
	return true;
}

bool UBroadSword::UseWeapon_Implementation(AAvatar * DamageCauser, UPARAM(ref)FDamageStruct & Damage, AActor * DamageTarget) {

	return true;
}
