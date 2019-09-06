// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleAxe.h"

#include "ConstructorHelpers.h"
#include "Interfaces/ComponentInterface.h"

UBattleAxe::UBattleAxe() {
	//ImageTexture = CreateDefaultSubobject<UTexture2D>("Image");
	Actions = TArray<EItemAction>();
	//TODO:Replace image texture to get it from the item index table
	ConstructorHelpers::FObjectFinder<UTexture2D> TextureFinder(TEXT("/Game/UserInterface/Icons/axe.axe"));
	if (TextureFinder.Succeeded()) {
		ImageTexture = TextureFinder.Object;
	}
	ItemName = "Battle Axe";
	MaxStackSize = 1;
}

UItem** UBattleAxe::GetComponent(EAssemblyComponentType Type){
	switch (Type) {
	case EAssemblyComponentType::ECT_AXE_HEAD:
		return &AxeHead;
	case EAssemblyComponentType::ECT_M_POMMEL:
		return &Pommel;
	case EAssemblyComponentType::ECT_M_GRIP:
		return &Grip;
	case EAssemblyComponentType::ECT_S_HANDLE:
		return &ShortHandle;
	}
	return nullptr;
}

bool UBattleAxe::SetWeaponMode_Implementation(int Mode) {
	return false;
}

float UBattleAxe::GetWeaponRange_Implementation() {
	return 0.0f;
}

float UBattleAxe::GetWeaponAttackDuration_Implementation() {
	return 0.0f;
}

float UBattleAxe::GetWeaponAttackCooldown_Implementation() {
	return 0.0f;
}

bool UBattleAxe::GetDamageStruct_Implementation(UPARAM(ref)FDamageStruct & Damage) {
	return true;
}

bool UBattleAxe::CanUseWeapon_Implementation(AAvatar * Avatar) {
	return true;
}

bool UBattleAxe::UseWeapon_Implementation(AAvatar * DamageCauser, UPARAM(ref)FDamageStruct & Damage, AActor * DamageTarget) {

	return true;
}
