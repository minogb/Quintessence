// Fill out your copyright notice in the Description page of Project Settings.

#include "Equipment.h"
#include "ConstructorHelpers.h"




UEquipment::UEquipment() {
	ConstructorHelpers::FObjectFinder<UTexture2D> TextureFinder(TEXT("/Game/UserInterface/Icons/axe.axe"));
	if (TextureFinder.Succeeded())
		ImageTexture = TextureFinder.Object;
	ItemId = 2;
	MaxStackSize = 1;
}