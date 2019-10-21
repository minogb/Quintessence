// Fill out your copyright notice in the Description page of Project Settings.


#include "Mallet.h"
#include "ConstructorHelpers.h"
#include "Interfaces/ComponentInterface.h"



UMallet::UMallet() {
	//ImageTexture = CreateDefaultSubobject<UTexture2D>("Image");
	Actions = TArray<EItemAction>();

	MaxStackSize = 1;
}

UItem** UMallet::GetComponent(EAssemblyComponentType Type) {
	switch (Type) {
	case EAssemblyComponentType::ECT_HAMMER_HEAD:
		return &HammerHead;
	case EAssemblyComponentType::ECT_BINDING:
		return &Binding;
	case EAssemblyComponentType::ECT_S_HANDLE:
		return &ShortHandle;
	}
	return nullptr;
}
bool UMallet::SetWeaponMode_Implementation(int Mode) {
	return false;
}

float UMallet::GetWeaponRange_Implementation() {
	return 0.0f;
}

float UMallet::GetWeaponAttackDuration_Implementation() {
	return 0.0f;
}

float UMallet::GetWeaponAttackCooldown_Implementation() {
	return 0.0f;
}

bool UMallet::GetDamageStruct_Implementation(UPARAM(ref)FDamageStruct & Damage) {
	return true;
}

bool UMallet::CanUseWeapon_Implementation(AAvatar * Avatar) {
	return true;
}

bool UMallet::UseWeapon_Implementation(AAvatar * DamageCauser, UPARAM(ref)FDamageStruct & Damage, AActor * DamageTarget) {

	return true;
}
