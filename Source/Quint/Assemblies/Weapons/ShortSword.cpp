// Fill out your copyright notice in the Description page of Project Settings.


#include "ShortSword.h"
#include "ConstructorHelpers.h"
#include "Interfaces/ComponentInterface.h"
#include "Json/Public/Serialization/JsonReader.h"
#include "Json/Public/Serialization/JsonSerializer.h"
#include "JsonUtilities/Public/JsonObjectConverter.h"



UShortSword::UShortSword() {
	//ImageTexture = CreateDefaultSubobject<UTexture2D>("Image");
	Actions = TArray<EItemAction>();
	ItemTableID = 10;
	MaxStackSize = 1;
}

FString UShortSword::GetSaveJSON()
{
	FString JSON;
	TSharedRef <TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&JSON);
	JsonWriter->WriteObjectStart();
	JsonWriter->WriteValue("UniqueID", UniqueItemId);
	JsonWriter->WriteValue("TableID", ItemTableID);
	if (MediumBlade) {
		JsonWriter->WriteRawJSONValue("MediumBlade", MediumBlade->GetSaveJSON());

	}
	else {
		JsonWriter->WriteObjectStart("MediumBlade");
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
	if (Guard) {
		JsonWriter->WriteRawJSONValue("Grip", Guard->GetSaveJSON());

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

void UShortSword::InitWithJson(TSharedPtr<FJsonObject> JsonData)
{
	if (JsonData) {
		if (JsonData->HasField("ID")) {
			UniqueItemId = JsonData->GetIntegerField("ID");
		}
		if (JsonData->HasField("MediumBlade")) {
			TSharedPtr<FJsonObject> cData = JsonData->GetObjectField("MediumBlade");
			if (cData->HasField("TableID")) {
				MediumBlade = UItem::CreateItemFromTable(cData->GetIntegerField("TableID"), Owner, cData);
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
		if (JsonData->HasField("Guard")) {
			TSharedPtr<FJsonObject> cData = JsonData->GetObjectField("Guard");
			if (cData->HasField("TableID")) {
				Guard = UItem::CreateItemFromTable(cData->GetIntegerField("TableID"), Owner, cData);
			}
		}
	}
}

UItem** UShortSword::GetComponent(EAssemblyComponentType Type){
	switch (Type) {
	case EAssemblyComponentType::ECT_M_BLADE:
		return &MediumBlade;
	case EAssemblyComponentType::ECT_M_POMMEL:
		return &Pommel;
	case EAssemblyComponentType::ECT_M_GRIP:
		return &Grip;
	case EAssemblyComponentType::ECT_GUARD:
		return &Guard;
	}
	return nullptr;
}


bool UShortSword::SetWeaponMode_Implementation(int Mode) {
	return false;
}

float UShortSword::GetWeaponRange_Implementation() {
	return 0.0f;
}

float UShortSword::GetWeaponAttackDuration_Implementation() {
	return 0.0f;
}

float UShortSword::GetWeaponAttackCooldown_Implementation() {
	return 0.0f;
}

bool UShortSword::GetDamageStruct_Implementation(UPARAM(ref)FDamageStruct & Damage) {
	return true;
}

bool UShortSword::CanUseWeapon_Implementation(AAvatar * Avatar) {
	return true;
}

bool UShortSword::UseWeapon_Implementation(AAvatar * DamageCauser, UPARAM(ref)FDamageStruct & Damage, AActor * DamageTarget) {

	return true;
}
