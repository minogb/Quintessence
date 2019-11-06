// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentStructure.h"
#include "Interfaces/Equipment.h"
#include "Item.h"
#include "Json/Public/Dom/JsonObject.h"
#include "Json/Public/Serialization/JsonReader.h"
#include "Json/Public/Serialization/JsonSerializer.h"

FString FEquipmentStruct::GetSaveJSON()
{
	FString JSON;
	TSharedRef <TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&JSON);

	JsonWriter->WriteObjectStart();
	if(IsValid(Helm))
		JsonWriter->WriteRawJSONValue("Helm", Helm->GetSaveJSON());
	else {
		JsonWriter->WriteObjectStart("Helm");
		JsonWriter->WriteValue("UniqueID", 0);
		JsonWriter->WriteObjectEnd();
	}
	if (IsValid(Chest))
		JsonWriter->WriteRawJSONValue("Chest", Chest->GetSaveJSON());
	else {
		JsonWriter->WriteObjectStart("Chest");
		JsonWriter->WriteValue("UniqueID", 0);
		JsonWriter->WriteObjectEnd();
	}
	if (IsValid(Leggings))
		JsonWriter->WriteRawJSONValue("Leggings", Leggings->GetSaveJSON());
	else {
		JsonWriter->WriteObjectStart("Leggings");
		JsonWriter->WriteValue("UniqueID", 0);
		JsonWriter->WriteObjectEnd();
	}
	if (IsValid(Boots))
		JsonWriter->WriteRawJSONValue("Boots", Boots->GetSaveJSON());
	else {
		JsonWriter->WriteObjectStart("Boots");
		JsonWriter->WriteValue("UniqueID", 0);
		JsonWriter->WriteObjectEnd();
	}
	if (IsValid(Gloves))
		JsonWriter->WriteRawJSONValue("Gloves", Gloves->GetSaveJSON());
	else {
		JsonWriter->WriteObjectStart("Gloves");
		JsonWriter->WriteValue("UniqueID", 0);
		JsonWriter->WriteObjectEnd();
	}
	if (IsValid(Weapon))
		JsonWriter->WriteRawJSONValue("Weapon", Weapon->GetSaveJSON());
	else {
		JsonWriter->WriteObjectStart("Weapon");
		JsonWriter->WriteValue("UniqueID", 0);
		JsonWriter->WriteObjectEnd();
	}
	if (IsValid(Sheild))
		JsonWriter->WriteRawJSONValue("Sheild", Sheild->GetSaveJSON());
	else {
		JsonWriter->WriteObjectStart("Shield");
		JsonWriter->WriteValue("UniqueID", 0);
		JsonWriter->WriteObjectEnd();
	}
	if (IsValid(Quiver))
		JsonWriter->WriteRawJSONValue("Quiver", Quiver->GetSaveJSON());
	else {
		JsonWriter->WriteObjectStart("Quiver");
		JsonWriter->WriteValue("UniqueID", 0);
		JsonWriter->WriteObjectEnd();
	}
	if (IsValid(Ring))
		JsonWriter->WriteRawJSONValue("Ring", Ring->GetSaveJSON());
	else {
		JsonWriter->WriteObjectStart("Ring");
		JsonWriter->WriteValue("UniqueID", 0);
		JsonWriter->WriteObjectEnd();
	}

	JsonWriter->WriteObjectEnd();
	JsonWriter->Close();
	return JSON;
}
void FEquipmentStruct::InitWithJSON(TSharedPtr<FJsonObject> InventoryJSON){

}
UItem * FEquipmentStruct::SetEquipment(UItem * Equipment, EEquipmentSlot Slot){
	UItem* retVal = NULL;
	if (IsValid(Equipment) && Equipment->GetClass()->ImplementsInterface(UEquipmentInterface::StaticClass())) {
		Slot = IEquipmentInterface::Execute_GetEquipmentSlot(Equipment);
	}
	switch (Slot) {
	case EEquipmentSlot::ES_HELM:
		retVal = Helm;
		Helm = Equipment;
		break;
	case EEquipmentSlot::ES_CHEST:
		retVal = Chest;
		Chest = Equipment;
		break;
	case EEquipmentSlot::ES_LEGGINGS:
		retVal = Leggings;
		Leggings = Equipment;
		break;
	case EEquipmentSlot::ES_BOOTS:
		retVal = Boots;
		Boots = Equipment;
		break;
	case EEquipmentSlot::ES_GLOVES:
		retVal = Gloves;
		Gloves = Equipment;
		break;
	case EEquipmentSlot::ES_QUIVER:
		retVal = Quiver;
		Quiver = Equipment;
		break;
	case EEquipmentSlot::ES_SHEILD:
		retVal = Sheild;
		Sheild = Equipment;
		break;
	case EEquipmentSlot::ES_RING:
		retVal = Ring;
		Ring = Equipment;
		break;
	case EEquipmentSlot::ES_WEAPON:
		retVal = Weapon;
		Weapon = Equipment;
		break;
	}
	return retVal;
}

UItem * FEquipmentStruct::Get(EEquipmentSlot Slot){
	switch (Slot) {
	case EEquipmentSlot::ES_HELM:
		return Helm;
		break;
	case EEquipmentSlot::ES_CHEST:
		return Chest;
		break;
	case EEquipmentSlot::ES_LEGGINGS:
		return Leggings;
		break;
	case EEquipmentSlot::ES_BOOTS:
		return Boots;
		break;
	case EEquipmentSlot::ES_GLOVES:
		return Gloves;
		break;
	case EEquipmentSlot::ES_QUIVER:
		return Quiver;
		break;
	case EEquipmentSlot::ES_SHEILD:
		return Sheild;
		break;
	case EEquipmentSlot::ES_RING:
		return Ring;
		break;
	case EEquipmentSlot::ES_WEAPON:
		return Weapon;
		break;
	}
	return NULL;
}

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Helm")
UItem* Helm;
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chest")
UItem* Chest;
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Leggings")
UItem* Leggings;
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boots")
UItem* Boots;
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gloves")
UItem* Gloves;
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
UItem* Weapon;
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sheild")
UItem* Sheild;
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quiver")
UItem* Quiver;
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ring")
UItem* Ring;
TArray<UItem*> FEquipmentStruct::GetAsList(){
	TArray<UItem*> retVal = TArray<UItem*>();
	retVal.Add(Helm);
	retVal.Add(Chest);
	retVal.Add(Leggings);
	retVal.Add(Boots);
	retVal.Add(Gloves);
	retVal.Add(Weapon);
	retVal.Add(Quiver);
	retVal.Add(Ring);
	return retVal;
}
