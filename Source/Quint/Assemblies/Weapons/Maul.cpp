// Fill out your copyright notice in the Description page of Project Settings.


#include "Maul.h"

#include "ConstructorHelpers.h"
#include "Interfaces/ComponentInterface.h"

UMaul::UMaul() {
	//ImageTexture = CreateDefaultSubobject<UTexture2D>("Image");
	Actions = TArray<EItemAction>();
	//TODO:Replace image texture to get it from the item index table
	ConstructorHelpers::FObjectFinder<UTexture2D> TextureFinder(TEXT("/Game/UserInterface/Icons/axe.axe"));
	if (TextureFinder.Succeeded()) {
		ImageTexture = TextureFinder.Object;
	}
	ItemName = "Maul";
	MaxStackSize = 1;
}

UItem * UMaul::GetComponent(EAssemblyComponentType Type) {/*
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

bool UMaul::SetComponent(UItem * Item) {/*
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