// Fill out your copyright notice in the Description page of Project Settings.


#include "ShortSword.h"
#include "ConstructorHelpers.h"
#include "Interfaces/ComponentInterface.h"



UShortSword::UShortSword() {
	//ImageTexture = CreateDefaultSubobject<UTexture2D>("Image");
	Actions = TArray<EItemAction>();
	//TODO:Replace image texture to get it from the item index table
	ConstructorHelpers::FObjectFinder<UTexture2D> TextureFinder(TEXT("/Game/UserInterface/Icons/axe.axe"));
	if (TextureFinder.Succeeded()) {
		ImageTexture = TextureFinder.Object;
	}
	ItemName = "Short Sword";
	MaxStackSize = 1;
}

UItem** UShortSword::GetComponent(EAssemblyComponentType Type){
	switch (Type) {
	case EAssemblyComponentType::ECT_M_BLADE:
		return &MediumBlade;
	case EAssemblyComponentType::ECT_M_POMMEL:
		return &Pommel;
	case EAssemblyComponentType::ECT_M_GRIP:
		return &Grip;
	case EAssemblyComponentType::ECT_GUARD:
		return &Guard;
	}
	return nullptr;
}


bool UShortSword::SetWeaponMode_Implementation(int Mode) {
	return false;
}

float UShortSword::GetWeaponRange_Implementation() {
	return 0.0f;
}

float UShortSword::GetWeaponAttackDuration_Implementation() {
	return 0.0f;
}

float UShortSword::GetWeaponAttackCooldown_Implementation() {
	return 0.0f;
}

bool UShortSword::GetDamageStruct_Implementation(UPARAM(ref)FDamageStruct & Damage) {
	return true;
}

bool UShortSword::CanUseWeapon_Implementation(AAvatar * Avatar) {
	return true;
}

bool UShortSword::UseWeapon_Implementation(AAvatar * DamageCauser, UPARAM(ref)FDamageStruct & Damage, AActor * DamageTarget) {

	return true;
}
