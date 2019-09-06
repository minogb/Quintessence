// Fill out your copyright notice in the Description page of Project Settings.


#include "Spear.h"
#include "ConstructorHelpers.h"
#include "Interfaces/ComponentInterface.h"

USpear::USpear() {
	//ImageTexture = CreateDefaultSubobject<UTexture2D>("Image");
	Actions = TArray<EItemAction>();
	//TODO:Replace image texture to get it from the item index table
	ConstructorHelpers::FObjectFinder<UTexture2D> TextureFinder(TEXT("/Game/UserInterface/Icons/axe.axe"));
	if (TextureFinder.Succeeded()) {
		ImageTexture = TextureFinder.Object;
	}
	ItemName = "Spear";
	MaxStackSize = 1;
}


UItem** USpear::GetComponent(EAssemblyComponentType Type) {
	switch (Type) {
	case EAssemblyComponentType::ECT_SPIKE:
		return &Spike;
	case EAssemblyComponentType::ECT_BINDING:
		return &Binding;
	case EAssemblyComponentType::ECT_M_HANDLE:
		return &MediumHandle;
	}
	return nullptr;
}
bool USpear::SetWeaponMode_Implementation(int Mode) {
	return false;
}

float USpear::GetWeaponRange_Implementation() {
	return 0.0f;
}

float USpear::GetWeaponAttackDuration_Implementation() {
	return 0.0f;
}

float USpear::GetWeaponAttackCooldown_Implementation() {
	return 0.0f;
}

bool USpear::GetDamageStruct_Implementation(UPARAM(ref)FDamageStruct & Damage) {
	return true;
}

bool USpear::CanUseWeapon_Implementation(AAvatar * Avatar) {
	return true;
}

bool USpear::UseWeapon_Implementation(AAvatar * DamageCauser, UPARAM(ref)FDamageStruct & Damage, AActor * DamageTarget) {

	return true;
}

