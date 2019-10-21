// Fill out your copyright notice in the Description page of Project Settings.


#include "Halberd.h"

#include "ConstructorHelpers.h"
#include "Interfaces/ComponentInterface.h"

UHalberd::UHalberd() {
	//ImageTexture = CreateDefaultSubobject<UTexture2D>("Image");
	Actions = TArray<EItemAction>();

	MaxStackSize = 1;
}

UItem** UHalberd::GetComponent(EAssemblyComponentType Type){
	switch (Type) {
	case EAssemblyComponentType::ECT_AXE_HEAD:
		return &AxeHead;
	case EAssemblyComponentType::ECT_SPIKE:
		return &Spike;
	case EAssemblyComponentType::ECT_L_GRIP:
		return &LongGrip;
	case EAssemblyComponentType::ECT_L_HANDLE:
		return &LongHandle;
	}
	return nullptr;
}

bool UHalberd::SetWeaponMode_Implementation(int Mode) {
	return false;
}

float UHalberd::GetWeaponRange_Implementation() {
	return 0.0f;
}

float UHalberd::GetWeaponAttackDuration_Implementation() {
	return 0.0f;
}

float UHalberd::GetWeaponAttackCooldown_Implementation() {
	return 0.0f;
}

bool UHalberd::GetDamageStruct_Implementation(UPARAM(ref)FDamageStruct & Damage) {
	return true;
}

bool UHalberd::CanUseWeapon_Implementation(AAvatar * Avatar) {
	return true;
}

bool UHalberd::UseWeapon_Implementation(AAvatar * DamageCauser, UPARAM(ref)FDamageStruct & Damage, AActor * DamageTarget) {

	return true;
}

