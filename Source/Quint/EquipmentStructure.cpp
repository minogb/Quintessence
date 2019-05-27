// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentStructure.h"
#include "Equipment.h"
UEquipment * FEquipmentStruct::SetEquipment(UEquipment * Equipment, EEquipmentType Slot){
	UEquipment* retVal = NULL;
	if (IsValid(Equipment)) {
		Slot = Equipment->GetSlot();
	}
	switch (Slot) {
	case EEquipmentType::ET_HELM:
		retVal = Helm;
		Helm = Equipment;
		break;
	case EEquipmentType::ET_CHEST:
		retVal = Chest;
		Chest = Equipment;
		break;
	case EEquipmentType::ET_LEGGINGS:
		retVal = Leggings;
		Leggings = Equipment;
		break;
	case EEquipmentType::ET_BOOTS:
		retVal = Boots;
		Boots = Equipment;
		break;
	case EEquipmentType::ET_GLOVES:
		retVal = Gloves;
		Gloves = Equipment;
		break;
	case EEquipmentType::ET_QUIVER:
		retVal = Quiver;
		Quiver = Equipment;
		break;
	case EEquipmentType::ET_SHEILD:
		retVal = Sheild;
		Sheild = Equipment;
		break;
	case EEquipmentType::ET_RING:
		retVal = Ring;
		Ring = Equipment;
		break;
	case EEquipmentType::ET_WEAPON:
		retVal = Weapon;
		Weapon = Equipment;
		break;
	}
	return retVal;
}

UEquipment * FEquipmentStruct::Get(EEquipmentType Slot){
	switch (Slot) {
	case EEquipmentType::ET_HELM:
		return Helm;
		break;
	case EEquipmentType::ET_CHEST:
		return Chest;
		break;
	case EEquipmentType::ET_LEGGINGS:
		return Leggings;
		break;
	case EEquipmentType::ET_BOOTS:
		return Boots;
		break;
	case EEquipmentType::ET_GLOVES:
		return Gloves;
		break;
	case EEquipmentType::ET_QUIVER:
		return Quiver;
		break;
	case EEquipmentType::ET_SHEILD:
		return Sheild;
		break;
	case EEquipmentType::ET_RING:
		return Ring;
		break;
	case EEquipmentType::ET_WEAPON:
		return Weapon;
		break;
	}
	return NULL;
}
