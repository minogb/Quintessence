// Fill out your copyright notice in the Description page of Project Settings.


#include "BroadSword.h"
#include "ConstructorHelpers.h"
#include "Interfaces/ComponentInterface.h"


UBroadSword::UBroadSword() {
	//ImageTexture = CreateDefaultSubobject<UTexture2D>("Image");
	Actions = TArray<EItemAction>();
	//TODO:Replace image texture to get it from the item index table
	ConstructorHelpers::FObjectFinder<UTexture2D> TextureFinder(TEXT("/Game/UserInterface/Icons/axe.axe"));
	if (TextureFinder.Succeeded()) {
		ImageTexture = TextureFinder.Object;
	}
	ItemName = "Broad Sword";
	MaxStackSize = 1;
}

UItem** UBroadSword::GetComponent(EAssemblyComponentType Type){
	switch (Type) {
	case EAssemblyComponentType::ECT_H_BLADE:
		return &HeavyBlade;
	case EAssemblyComponentType::ECT_M_POMMEL:
		return &Pommel;
	case EAssemblyComponentType::ECT_L_GRIP:
		return &LongGrip;
	case EAssemblyComponentType::ECT_GUARD:
		return &Guard;
	}
	return nullptr;
}

bool UBroadSword::SetWeaponMode_Implementation(int Mode) {
	return false;
}

float UBroadSword::GetWeaponRange_Implementation() {
	return 0.0f;
}

float UBroadSword::GetWeaponAttackDuration_Implementation() {
	return 0.0f;
}

float UBroadSword::GetWeaponAttackCooldown_Implementation() {
	return 0.0f;
}

bool UBroadSword::GetDamageStruct_Implementation(UPARAM(ref)FDamageStruct & Damage) {
	return true;
}

bool UBroadSword::CanUseWeapon_Implementation(AAvatar * Avatar) {
	return true;
}

bool UBroadSword::UseWeapon_Implementation(AAvatar * DamageCauser, UPARAM(ref)FDamageStruct & Damage, AActor * DamageTarget) {

	return true;
}
