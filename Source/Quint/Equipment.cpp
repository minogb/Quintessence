// Fill out your copyright notice in the Description page of Project Settings.

#include "Equipment.h"
#include "ConstructorHelpers.h"
#include "EquipmentComponent.h"



UEquipment::UEquipment() {
	ConstructorHelpers::FObjectFinder<UTexture2D> TextureFinder(TEXT("/Game/UserInterface/Icons/axe.axe"));
	if (TextureFinder.Succeeded())
		ImageTexture = TextureFinder.Object;
	ItemId = 2;
	MaxStackSize = 1;
}

TArray<EEquipmentComponentType> UEquipment::GetRequiredComponentTypes(){
	TArray<EEquipmentComponentType> retVal = TArray<EEquipmentComponentType>();
	Components.GetKeys(retVal);
	return retVal;
}

bool UEquipment::InitComponents(TMap<EEquipmentComponentType, UEquipmentComponent*>& InitComponents){
	bool success = false;
	for (const auto& current : InitComponents) {
		if (!Components.Contains(current.Key)) {
			success = false;
		}
	}
	if (success) {
		for (const auto& current : InitComponents) {
			Components[current.Key] = current.Value;
		}
		InitComponents.Empty();
	}
	return success;
}
