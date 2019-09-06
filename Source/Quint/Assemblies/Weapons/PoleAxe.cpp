// Fill out your copyright notice in the Description page of Project Settings.


#include "PoleAxe.h"
#include "ConstructorHelpers.h"
#include "Interfaces/ComponentInterface.h"

UPoleAxe::UPoleAxe() {
	//ImageTexture = CreateDefaultSubobject<UTexture2D>("Image");
	Actions = TArray<EItemAction>();
	//TODO:Replace image texture to get it from the item index table
	ConstructorHelpers::FObjectFinder<UTexture2D> TextureFinder(TEXT("/Game/UserInterface/Icons/axe.axe"));
	if (TextureFinder.Succeeded()) {
		ImageTexture = TextureFinder.Object;
	}
	ItemName = "Pole Axe";
	MaxStackSize = 1;
}

UItem** UPoleAxe::GetComponent(EAssemblyComponentType Type){
	switch (Type) {
	case EAssemblyComponentType::ECT_AXE_HEAD:
		return &AxeHead;
	case EAssemblyComponentType::ECT_HAMMER_HEAD:
		return &HammerHead;
	case EAssemblyComponentType::ECT_L_GRIP:
		return &LongGrip;
	case EAssemblyComponentType::ECT_L_HANDLE:
		return &LongHandle;
	}
	return nullptr;
}


bool UPoleAxe::SetWeaponMode_Implementation(int Mode) {
	return false;
}

float UPoleAxe::GetWeaponRange_Implementation() {
	return 0.0f;
}

float UPoleAxe::GetWeaponAttackDuration_Implementation() {
	return 0.0f;
}

float UPoleAxe::GetWeaponAttackCooldown_Implementation() {
	return 0.0f;
}

bool UPoleAxe::GetDamageStruct_Implementation(UPARAM(ref)FDamageStruct & Damage) {
	return true;
}

bool UPoleAxe::CanUseWeapon_Implementation(AAvatar * Avatar) {
	return true;
}

bool UPoleAxe::UseWeapon_Implementation(AAvatar * DamageCauser, UPARAM(ref)FDamageStruct & Damage, AActor * DamageTarget) {

	return true;
}