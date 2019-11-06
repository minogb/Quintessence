// Fill out your copyright notice in the Description page of Project Settings.


#include "Dagger.h"
#include "ConstructorHelpers.h"
#include "Interfaces/ComponentInterface.h"
#include "Json/Public/Serialization/JsonReader.h"
#include "Json/Public/Serialization/JsonSerializer.h"
#include "JsonUtilities/Public/JsonObjectConverter.h"


UDagger::UDagger() {
	//ImageTexture = CreateDefaultSubobject<UTexture2D>("Image");
	Actions = TArray<EItemAction>();
	ItemTableID = 18;
	MaxStackSize = 1;
}

FString UDagger::GetSaveJSON()
{
	FString JSON;
	TSharedRef <TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&JSON);
	JsonWriter->WriteObjectStart();
	JsonWriter->WriteValue("UniqueID", UniqueItemId);
	JsonWriter->WriteValue("TableID", ItemTableID);
	if (SmallBlade) {
		JsonWriter->WriteRawJSONValue("SmallBlade", SmallBlade->GetSaveJSON());

	}
	else {
		JsonWriter->WriteObjectStart("SmallBlade");
		JsonWriter->WriteValue("UniqueID", 0);
		JsonWriter->WriteObjectEnd();
	}
	if (ShortGrip) {
		JsonWriter->WriteRawJSONValue("ShortGrip", ShortGrip->GetSaveJSON());

	}
	else {
		JsonWriter->WriteObjectStart("ShortGrip");
		JsonWriter->WriteValue("UniqueID", 0);
		JsonWriter->WriteObjectEnd();
	}
	if (SmallPommel) {
		JsonWriter->WriteRawJSONValue("SmallPommel", SmallPommel->GetSaveJSON());

	}
	else {
		JsonWriter->WriteObjectStart("SmallPommel");
		JsonWriter->WriteValue("UniqueID", 0);
		JsonWriter->WriteObjectEnd();
	}
	JsonWriter->WriteObjectEnd();
	JsonWriter->Close();
	return JSON;
}

UItem** UDagger::GetComponent(EAssemblyComponentType Type){
	switch (Type) {
		case EAssemblyComponentType::ECT_S_BLADE:
			return &SmallBlade;
		case EAssemblyComponentType::ECT_S_GRIP:
			return &ShortGrip;
		case EAssemblyComponentType::ECT_S_POMMEL:
			return &SmallPommel;
	}
	return nullptr;
}

void UDagger::InitWithJson(TSharedPtr<FJsonObject> JsonData)
{
	if (JsonData) {
		if (JsonData->HasField("ID")) {
			UniqueItemId = JsonData->GetIntegerField("ID");
		}
		if (JsonData->HasField("SmallBlade")) {
			TSharedPtr<FJsonObject> cData = JsonData->GetObjectField("SmallBlade");
			if (cData->HasField("TableID")) {
				SmallBlade = UItem::CreateItemFromTable(cData->GetIntegerField("TableID"), Owner, cData);
			}
		}
		if (JsonData->HasField("ShortGrip")) {
			TSharedPtr<FJsonObject> cData = JsonData->GetObjectField("ShortGrip");
			if (cData->HasField("TableID")) {
				ShortGrip = UItem::CreateItemFromTable(cData->GetIntegerField("TableID"), Owner, cData);
			}
		}
		if (JsonData->HasField("SmallPommel")) {
			TSharedPtr<FJsonObject> cData = JsonData->GetObjectField("SmallPommel");
			if (cData->HasField("TableID")) {
				SmallPommel = UItem::CreateItemFromTable(cData->GetIntegerField("TableID"), Owner, cData);
			}
		}
	}
}

bool UDagger::SetWeaponMode_Implementation(int Mode){
	return false;
}

float UDagger::GetWeaponRange_Implementation(){
	return 0.0f;
}

float UDagger::GetWeaponAttackDuration_Implementation(){
	return 0.0f;
}

float UDagger::GetWeaponAttackCooldown_Implementation(){
	return 0.0f;
}

bool UDagger::GetDamageStruct_Implementation(UPARAM(ref)FDamageStruct & Damage){
	return true;
}

bool UDagger::CanUseWeapon_Implementation(AAvatar * Avatar){
	return true;
}

bool UDagger::UseWeapon_Implementation(AAvatar * DamageCauser, UPARAM(ref)FDamageStruct & Damage, AActor * DamageTarget){

	return true;
}
