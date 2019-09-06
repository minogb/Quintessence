// Fill out your copyright notice in the Description page of Project Settings.


#include "LongSword.h"
#include "ConstructorHelpers.h"
#include "Interfaces/ComponentInterface.h"


ULongSword::ULongSword() {
	//ImageTexture = CreateDefaultSubobject<UTexture2D>("Image");
	Actions = TArray<EItemAction>();
	//TODO:Replace image texture to get it from the item index table
	ConstructorHelpers::FObjectFinder<UTexture2D> TextureFinder(TEXT("/Game/UserInterface/Icons/axe.axe"));
	if (TextureFinder.Succeeded()) {
		ImageTexture = TextureFinder.Object;
	}
	ItemName = "Long Sword";
	MaxStackSize = 1;
}

UItem** ULongSword::GetComponent(EAssemblyComponentType Type){
	switch (Type) {
	case EAssemblyComponentType::ECT_L_BLADE:
		return &LongBlade;
	case EAssemblyComponentType::ECT_M_POMMEL:
		return &Pommel;
	case EAssemblyComponentType::ECT_GUARD:
		return &Guard;
	case EAssemblyComponentType::ECT_L_GRIP:
		return &LongGrip;
	}
	return nullptr;
}

bool ULongSword::SetWeaponMode_Implementation(int Mode) {
	return false;
}

float ULongSword::GetWeaponRange_Implementation() {
	return 0.0f;
}

float ULongSword::GetWeaponAttackDuration_Implementation() {
	return 0.0f;
}

float ULongSword::GetWeaponAttackCooldown_Implementation() {
	return 0.0f;
}

bool ULongSword::GetDamageStruct_Implementation(UPARAM(ref)FDamageStruct & Damage) {
	return true;
}

bool ULongSword::CanUseWeapon_Implementation(AAvatar * Avatar) {
	return true;
}

bool ULongSword::UseWeapon_Implementation(AAvatar * DamageCauser, UPARAM(ref)FDamageStruct & Damage, AActor * DamageTarget) {

	return true;
}
