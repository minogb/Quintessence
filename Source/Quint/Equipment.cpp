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


bool UEquipment::InitComponents_Implementation(TMap<EEquipmentComponentType, UEquipmentComponent*> InitComponents){
	return false;
}

TMap<EEquipmentComponentType, UEquipmentComponent*> UEquipment::GetComponents_Implementation()
{
	return TMap<EEquipmentComponentType, UEquipmentComponent*>();
}
