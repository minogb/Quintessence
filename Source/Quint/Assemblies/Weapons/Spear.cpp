// Fill out your copyright notice in the Description page of Project Settings.


#include "Spear.h"
#include "ConstructorHelpers.h"
#include "Interfaces/ComponentInterface.h"
#include "Json/Public/Serialization/JsonReader.h"
#include "Json/Public/Serialization/JsonSerializer.h"
#include "JsonUtilities/Public/JsonObjectConverter.h"

USpear::USpear() {
	//ImageTexture = CreateDefaultSubobject<UTexture2D>("Image");
	Actions = TArray<EItemAction>();
	ItemTableID = 9;
	MaxStackSize = 1;
}

FString USpear::GetSaveJSON()
{
	FString JSON;
	TSharedRef <TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&JSON);
	JsonWriter->WriteObjectStart();
	JsonWriter->WriteValue("UniqueID", UniqueItemId);
	JsonWriter->WriteValue("TableID", ItemTableID);
	if (Spike) {
		JsonWriter->WriteRawJSONValue("Spike", Spike->GetSaveJSON());

	}
	else {
		JsonWriter->WriteObjectStart("Spike");
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
	if (MediumHandle) {
		JsonWriter->WriteRawJSONValue("MediumHandle", MediumHandle->GetSaveJSON());

	}
	else {
		JsonWriter->WriteObjectStart("MediumHandle");
		JsonWriter->WriteValue("UniqueID", 0);
		JsonWriter->WriteObjectEnd();
	}
	JsonWriter->WriteObjectEnd();
	JsonWriter->Close();
	return JSON;
}

void USpear::InitWithJson(TSharedPtr<FJsonObject> JsonData)
{
	if (JsonData) {
		if (JsonData->HasField("ID")) {
			UniqueItemId = JsonData->GetIntegerField("ID");
		}
		if (JsonData->HasField("Spike")) {
			TSharedPtr<FJsonObject> cData = JsonData->GetObjectField("Spike");
			if (cData->HasField("TableID")) {
				Spike = UItem::CreateItemFromTable(cData->GetIntegerField("TableID"), Owner, cData);
			}
		}
		if (JsonData->HasField("Binding")) {
			TSharedPtr<FJsonObject> cData = JsonData->GetObjectField("Binding");
			if (cData->HasField("TableID")) {
				Binding = UItem::CreateItemFromTable(cData->GetIntegerField("TableID"), Owner, cData);
			}
		}
		if (JsonData->HasField("MediumHandle")) {
			TSharedPtr<FJsonObject> cData = JsonData->GetObjectField("MediumHandle");
			if (cData->HasField("TableID")) {
				MediumHandle = UItem::CreateItemFromTable(cData->GetIntegerField("TableID"), Owner, cData);
			}
		}
	}
}


UItem** USpear::GetComponent(EAssemblyComponentType Type) {
	switch (Type) {
	case EAssemblyComponentType::ECT_SPIKE:
		return &Spike;
	case EAssemblyComponentType::ECT_BINDING:
		return &Binding;
	case EAssemblyComponentType::ECT_M_HANDLE:
		return &MediumHandle;
	}
	return nullptr;
}
bool USpear::SetWeaponMode_Implementation(int Mode) {
	return false;
}

float USpear::GetWeaponRange_Implementation() {
	return 0.0f;
}

float USpear::GetWeaponAttackDuration_Implementation() {
	return 0.0f;
}

float USpear::GetWeaponAttackCooldown_Implementation() {
	return 0.0f;
}

bool USpear::GetDamageStruct_Implementation(UPARAM(ref)FDamageStruct & Damage) {
	return true;
}

bool USpear::CanUseWeapon_Implementation(AAvatar * Avatar) {
	return true;
}

bool USpear::UseWeapon_Implementation(AAvatar * DamageCauser, UPARAM(ref)FDamageStruct & Damage, AActor * DamageTarget) {

	return true;
}

