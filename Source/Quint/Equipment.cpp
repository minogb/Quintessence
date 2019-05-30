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
	static ConstructorHelpers::FObjectFinder<UDataTable> EquipmentDataTableGet(TEXT("/Game/Equipment/RequiredComponentsForEquipmentTable"));
	if (EquipmentDataTableGet.Succeeded()) {
		EquipmentDataTable = EquipmentDataTableGet.Object;
	}
}

TArray<EEquipmentComponentType> UEquipment::GetRequiredComponentTypes(){
	TArray<EEquipmentComponentType> retVal = TArray<EEquipmentComponentType>();
	Components.GetKeys(retVal);
	return retVal;
}

bool UEquipment::InitComponents(FName EquipmentType, TMap<EEquipmentComponentType, UEquipmentComponent*>& InitComponents){
	Components.Empty();
	bool success = false; 
	if (IsValid(EquipmentDataTable)) {
		static const FString Context(TEXT("Equipment Context"));
		FEquipmentBuildingStruct* row = EquipmentDataTable->FindRow< FEquipmentBuildingStruct>(EquipmentType, Context, true);
		if (row) {
			//Do we have anything we don't need?
			for (const auto& current : InitComponents) {
				if (row->Components.Contains(current.Key)) {
					return false;
				}
			}
			//Do we have everything we need? + Init compnonents array
			for (const auto& current : row->Components) {
				if (InitComponents.Contains(current))
					Components.Add(current,InitComponents[current]);
				else {
					success = false;
					break;
				}
			}
			if (success)
				InitComponents.Empty();
			else
				Components.Empty();
		}
	}
	return success;
}

int UEquipment::GetHarvestLevelOfType_Implementation(EHarvestType Type){
	int highest = 0;
	for (const auto& current : Components) {
		
	}
	return highest;
}
