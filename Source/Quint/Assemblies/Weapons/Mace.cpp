// Fill out your copyright notice in the Description page of Project Settings.


#include "Mace.h"

#include "ConstructorHelpers.h"
#include "Interfaces/ComponentInterface.h"

UMace::UMace() {
	//ImageTexture = CreateDefaultSubobject<UTexture2D>("Image");
	Actions = TArray<EItemAction>();
	//TODO:Replace image texture to get it from the item index table
	ConstructorHelpers::FObjectFinder<UTexture2D> TextureFinder(TEXT("/Game/UserInterface/Icons/axe.axe"));
	if (TextureFinder.Succeeded()) {
		ImageTexture = TextureFinder.Object;
	}
	ItemName = "Mace";
	MaxStackSize = 1;
}

UItem** UMace::GetComponent(EAssemblyComponentType Type){
	switch (Type) {
	case EAssemblyComponentType::ECT_HAMMER_HEAD:
		return &HammerHead;
	case EAssemblyComponentType::ECT_SPIKE:
		return &Spike;
	case EAssemblyComponentType::ECT_S_HANDLE:
		return &ShortHandle;
	}
	return nullptr;
}

bool UMace::SetWeaponMode_Implementation(int Mode) {
	return false;
}

float UMace::GetWeaponRange_Implementation() {
	return 0.0f;
}

float UMace::GetWeaponAttackDuration_Implementation() {
	return 0.0f;
}

float UMace::GetWeaponAttackCooldown_Implementation() {
	return 0.0f;
}

bool UMace::GetDamageStruct_Implementation(UPARAM(ref)FDamageStruct & Damage) {
	return true;
}

bool UMace::CanUseWeapon_Implementation(AAvatar * Avatar) {
	return true;
}

bool UMace::UseWeapon_Implementation(AAvatar * DamageCauser, UPARAM(ref)FDamageStruct & Damage, AActor * DamageTarget) {

	return true;
}