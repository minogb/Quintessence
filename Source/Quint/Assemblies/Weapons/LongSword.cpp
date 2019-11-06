// Fill out your copyright notice in the Description page of Project Settings.


#include "LongSword.h"
#include "ConstructorHelpers.h"
#include "Interfaces/ComponentInterface.h"
#include "Json/Public/Serialization/JsonReader.h"
#include "Json/Public/Serialization/JsonSerializer.h"
#include "JsonUtilities/Public/JsonObjectConverter.h"


ULongSword::ULongSword() {
	//ImageTexture = CreateDefaultSubobject<UTexture2D>("Image");
	Actions = TArray<EItemAction>();
	ItemTableID = 15;
	MaxStackSize = 1;
}

FString ULongSword::GetSaveJSON()
{
	FString JSON;
	TSharedRef <TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&JSON);
	JsonWriter->WriteObjectStart();
	JsonWriter->WriteValue("UniqueID", UniqueItemId);
	JsonWriter->WriteValue("TableID", ItemTableID);
	if (LongBlade) {
		JsonWriter->WriteRawJSONValue("LongBlade", LongBlade->GetSaveJSON());

	}
	else {
		JsonWriter->WriteObjectStart("LongBlade");
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
	if (Guard) {
		JsonWriter->WriteRawJSONValue("Guard", Guard->GetSaveJSON());

	}
	else {
		JsonWriter->WriteObjectStart("Guard");
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
	JsonWriter->WriteObjectEnd();
	JsonWriter->Close();
	return JSON;
}

UItem** ULongSword::GetComponent(EAssemblyComponentType Type){
	switch (Type) {
	case EAssemblyComponentType::ECT_L_BLADE:
		return &LongBlade;
	case EAssemblyComponentType::ECT_M_POMMEL:
		return &Pommel;
	case EAssemblyComponentType::ECT_GUARD:
		return &Guard;
	case EAssemblyComponentType::ECT_L_GRIP:
		return &LongGrip;
	}
	return nullptr;
}

void ULongSword::InitWithJson(TSharedPtr<FJsonObject> JsonData)
{
	if (JsonData) {
		if (JsonData->HasField("ID")) {
			UniqueItemId = JsonData->GetIntegerField("ID");
		}
		if (JsonData->HasField("LongBlade")) {
			TSharedPtr<FJsonObject> cData = JsonData->GetObjectField("LongBlade");
			if (cData->HasField("TableID")) {
				LongBlade = UItem::CreateItemFromTable(cData->GetIntegerField("TableID"), Owner, cData);
			}
		}
		if (JsonData->HasField("Pommel")) {
			TSharedPtr<FJsonObject> cData = JsonData->GetObjectField("Pommel");
			if (cData->HasField("TableID")) {
				Pommel = UItem::CreateItemFromTable(cData->GetIntegerField("TableID"), Owner, cData);
			}
		}
		if (JsonData->HasField("Guard")) {
			TSharedPtr<FJsonObject> cData = JsonData->GetObjectField("Guard");
			if (cData->HasField("TableID")) {
				Guard = UItem::CreateItemFromTable(cData->GetIntegerField("TableID"), Owner, cData);
			}
		}
		if (JsonData->HasField("LongGrip")) {
			TSharedPtr<FJsonObject> cData = JsonData->GetObjectField("LongGrip");
			if (cData->HasField("TableID")) {
				LongGrip = UItem::CreateItemFromTable(cData->GetIntegerField("TableID"), Owner, cData);
			}
		}
	}
}

bool ULongSword::SetWeaponMode_Implementation(int Mode) {
	return false;
}

float ULongSword::GetWeaponRange_Implementation() {
	return 0.0f;
}

float ULongSword::GetWeaponAttackDuration_Implementation() {
	return 0.0f;
}

float ULongSword::GetWeaponAttackCooldown_Implementation() {
	return 0.0f;
}

bool ULongSword::GetDamageStruct_Implementation(UPARAM(ref)FDamageStruct & Damage) {
	return true;
}

bool ULongSword::CanUseWeapon_Implementation(AAvatar * Avatar) {
	return true;
}

bool ULongSword::UseWeapon_Implementation(AAvatar * DamageCauser, UPARAM(ref)FDamageStruct & Damage, AActor * DamageTarget) {

	return true;
}
