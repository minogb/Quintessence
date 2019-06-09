// Fill out your copyright notice in the Description page of Project Settings.

#include "Equipment.h"
#include "ConstructorHelpers.h"
#include "EquipmentComponent.h"
#include "Item.h"

UEquipment::UEquipment() {
	ConstructorHelpers::FObjectFinder<UTexture2D> TextureFinder(TEXT("/Game/UserInterface/Icons/axe.axe"));
	if (TextureFinder.Succeeded())
		ImageTexture = TextureFinder.Object;
	ItemTypeId = 2;
	MaxStackSize = 1;
}


bool UEquipment::InitComponents(TMap<EEquipmentComponentType, UEquipmentComponent*> InitComponents){

	for (TPair<EEquipmentComponentType,UEquipmentComponent*> &current : Components) {
		if (InitComponents.Contains(current.Key)) {
			current.Value = *InitComponents.Find(current.Key);
		}
		else {
			Components.Empty();
			return false;
		}
	}
	for (TPair<EEquipmentComponentType, UEquipmentComponent*> &current : Components) {
		if (InitComponents.Contains(current.Key)) {
			InitComponents.Remove(current.Key);
		}
	}

	return true;
}

TMap<EEquipmentComponentType, UEquipmentComponent*> UEquipment::GetComponents_Implementation(){
	return Components;
}

int UEquipment::GetHarvestLevelOfType_Implementation(EHarvestType Type)
{
	int highest = 0;
	for (TPair<EEquipmentComponentType, UEquipmentComponent*> &current : Components) {
		int currentValue = current.Value->GetHarvestLevel(Type);
		if (currentValue > highest) {
			highest = currentValue;
		}
	}
	return highest;
}

int UEquipment::GetRequiredUseLevel_Implementation(EHarvestType Type)
{
	return 0;
}
