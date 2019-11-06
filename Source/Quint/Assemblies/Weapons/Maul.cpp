// Fill out your copyright notice in the Description page of Project Settings.


#include "Maul.h"

#include "ConstructorHelpers.h"
#include "Interfaces/ComponentInterface.h"
#include "Json/Public/Serialization/JsonReader.h"
#include "Json/Public/Serialization/JsonSerializer.h"
#include "JsonUtilities/Public/JsonObjectConverter.h"

UMaul::UMaul() {
	//ImageTexture = CreateDefaultSubobject<UTexture2D>("Image");
	Actions = TArray<EItemAction>();
	ItemTableID = 12;
	MaxStackSize = 1;
}

FString UMaul::GetSaveJSON()
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

UItem** UMaul::GetComponent(EAssemblyComponentType Type){
	switch (Type) {
	case EAssemblyComponentType::ECT_L_HAMMER_HEAD:
		return &LargeHammerHead;
	case EAssemblyComponentType::ECT_BINDING:
		return &Binding;
	case EAssemblyComponentType::ECT_M_HANDLE:
		return &MediumHandle;
	}
	return nullptr;
}

void UMaul::InitWithJson(TSharedPtr<FJsonObject> JsonData)
{
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


bool UMaul::SetWeaponMode_Implementation(int Mode) {
	return false;
}

float UMaul::GetWeaponRange_Implementation() {
	return 0.0f;
}

float UMaul::GetWeaponAttackDuration_Implementation() {
	return 0.0f;
}

float UMaul::GetWeaponAttackCooldown_Implementation() {
	return 0.0f;
}

bool UMaul::GetDamageStruct_Implementation(UPARAM(ref)FDamageStruct & Damage) {
	return true;
}

bool UMaul::CanUseWeapon_Implementation(AAvatar * Avatar) {
	return true;
}

bool UMaul::UseWeapon_Implementation(AAvatar * DamageCauser, UPARAM(ref)FDamageStruct & Damage, AActor * DamageTarget) {

	return true;
}