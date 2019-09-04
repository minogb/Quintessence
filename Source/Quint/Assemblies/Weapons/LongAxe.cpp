// Fill out your copyright notice in the Description page of Project Settings.


#include "LongAxe.h"

#include "ConstructorHelpers.h"
#include "Interfaces/ComponentInterface.h"

ULongAxe::ULongAxe() {
	//ImageTexture = CreateDefaultSubobject<UTexture2D>("Image");
	Actions = TArray<EItemAction>();
	//TODO:Replace image texture to get it from the item index table
	ConstructorHelpers::FObjectFinder<UTexture2D> TextureFinder(TEXT("/Game/UserInterface/Icons/axe.axe"));
	if (TextureFinder.Succeeded()) {
		ImageTexture = TextureFinder.Object;
	}
	ItemName = "Long Axe";
	MaxStackSize = 1;
}

UItem** ULongAxe::GetComponent(EAssemblyComponentType Type){/*
	switch (Type) {
	case EAssemblyComponentType::ECT_S_BLADE:
		return SmallBlade;
	case EAssemblyComponentType::ECT_S_GRIP:
		return ShortGrip;
	case EAssemblyComponentType::ECT_S_POMMEL:
		return SmallPommel;
	}*/
	return nullptr;
}

bool ULongAxe::SetWeaponMode_Implementation(int Mode) {
	return false;
}

float ULongAxe::GetWeaponRange_Implementation() {
	return 0.0f;
}

float ULongAxe::GetWeaponAttackDuration_Implementation() {
	return 0.0f;
}

float ULongAxe::GetWeaponAttackCooldown_Implementation() {
	return 0.0f;
}

bool ULongAxe::GetDamageStruct_Implementation(UPARAM(ref)FDamageStruct & Damage) {
	return true;
}

bool ULongAxe::CanUseWeapon_Implementation(AAvatar * Avatar) {
	return true;
}

bool ULongAxe::UseWeapon_Implementation(AAvatar * DamageCauser, UPARAM(ref)FDamageStruct & Damage, AActor * DamageTarget) {

	return true;
}