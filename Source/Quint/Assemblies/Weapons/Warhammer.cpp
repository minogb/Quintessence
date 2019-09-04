// Fill out your copyright notice in the Description page of Project Settings.


#include "Warhammer.h"

#include "ConstructorHelpers.h"
#include "Interfaces/ComponentInterface.h"


UWarhammer::UWarhammer() {
	//ImageTexture = CreateDefaultSubobject<UTexture2D>("Image");
	Actions = TArray<EItemAction>();
	//TODO:Replace image texture to get it from the item index table
	ConstructorHelpers::FObjectFinder<UTexture2D> TextureFinder(TEXT("/Game/UserInterface/Icons/axe.axe"));
	if (TextureFinder.Succeeded()) {
		ImageTexture = TextureFinder.Object;
	}
	ItemName = "War Hammer";
	MaxStackSize = 1;
}

UItem** UWarhammer::GetComponent(EAssemblyComponentType Type){/*
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


bool UWarhammer::SetWeaponMode_Implementation(int Mode) {
	return false;
}

float UWarhammer::GetWeaponRange_Implementation() {
	return 0.0f;
}

float UWarhammer::GetWeaponAttackDuration_Implementation() {
	return 0.0f;
}

float UWarhammer::GetWeaponAttackCooldown_Implementation() {
	return 0.0f;
}

bool UWarhammer::GetDamageStruct_Implementation(UPARAM(ref)FDamageStruct & Damage) {
	return true;
}

bool UWarhammer::CanUseWeapon_Implementation(AAvatar * Avatar) {
	return true;
}

bool UWarhammer::UseWeapon_Implementation(AAvatar * DamageCauser, UPARAM(ref)FDamageStruct & Damage, AActor * DamageTarget) {

	return true;
}