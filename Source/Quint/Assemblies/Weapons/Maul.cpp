// Fill out your copyright notice in the Description page of Project Settings.


#include "Maul.h"

#include "ConstructorHelpers.h"
#include "Interfaces/ComponentInterface.h"

UMaul::UMaul() {
	//ImageTexture = CreateDefaultSubobject<UTexture2D>("Image");
	Actions = TArray<EItemAction>();

	MaxStackSize = 1;
}

UItem** UMaul::GetComponent(EAssemblyComponentType Type){
	switch (Type) {
	case EAssemblyComponentType::ECT_L_HAMMER_HEAD:
		return &LargeHammerHead;
	case EAssemblyComponentType::ECT_BINDING:
		return &Binding;
	case EAssemblyComponentType::ECT_M_HANDLE:
		return &MediumHandle;
	}
	return nullptr;
}


bool UMaul::SetWeaponMode_Implementation(int Mode) {
	return false;
}

float UMaul::GetWeaponRange_Implementation() {
	return 0.0f;
}

float UMaul::GetWeaponAttackDuration_Implementation() {
	return 0.0f;
}

float UMaul::GetWeaponAttackCooldown_Implementation() {
	return 0.0f;
}

bool UMaul::GetDamageStruct_Implementation(UPARAM(ref)FDamageStruct & Damage) {
	return true;
}

bool UMaul::CanUseWeapon_Implementation(AAvatar * Avatar) {
	return true;
}

bool UMaul::UseWeapon_Implementation(AAvatar * DamageCauser, UPARAM(ref)FDamageStruct & Damage, AActor * DamageTarget) {

	return true;
}