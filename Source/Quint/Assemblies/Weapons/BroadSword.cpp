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

UItem * UBroadSword::GetComponent(EAssemblyComponentType Type) {/*
	switch (Type) {
	case EAssemblyComponentType::ECT_S_BLADE:
		return SmallBlade;
	case EAssemblyComponentType::ECT_S_GRIP:
		return ShortGrip;
	case EAssemblyComponentType::ECT_S_POMMEL:
		return SmallPommel;
	}*/
	return nullptr;
}

bool UBroadSword::SetComponent(UItem * Item) {/*
	EAssemblyComponentType type = EAssemblyComponentType::ECT_NONE;
	if (IsValid(Item) && Item->GetClass()->ImplementsInterface(UComponentInterface::StaticClass())) {
		type = IComponentInterface::Execute_GetComponentSlot(Item);
	}
	switch (type) {
	case EAssemblyComponentType::ECT_S_BLADE:
		SmallBlade = Item;
		return true;
		break;
	case EAssemblyComponentType::ECT_S_GRIP:
		ShortGrip = Item;
		return true;
		break;
	case EAssemblyComponentType::ECT_S_POMMEL:
		SmallPommel = Item;
		return true;
		break;
	default:
		return false;
		break;
	}
	*/
	return false;
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
