// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentStructure.h"
#include "Equipment.h"
#include "Item.h"
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
