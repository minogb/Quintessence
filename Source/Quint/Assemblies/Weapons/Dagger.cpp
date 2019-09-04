// Fill out your copyright notice in the Description page of Project Settings.


#include "Dagger.h"
#include "ConstructorHelpers.h"
#include "Interfaces/ComponentInterface.h"


UDagger::UDagger() {
	//ImageTexture = CreateDefaultSubobject<UTexture2D>("Image");
	Actions = TArray<EItemAction>();
	//TODO:Replace image texture to get it from the item index table
	ConstructorHelpers::FObjectFinder<UTexture2D> TextureFinder(TEXT("/Game/UserInterface/Icons/axe.axe"));
	if (TextureFinder.Succeeded()) {
		ImageTexture = TextureFinder.Object;
	}
	ItemName = "Dagger";
	MaxStackSize = 1;
}

UItem** UDagger::GetComponent(EAssemblyComponentType Type){
	switch (Type) {
		case EAssemblyComponentType::ECT_S_BLADE:
			return &SmallBlade;
		case EAssemblyComponentType::ECT_S_GRIP:
			return &ShortGrip;
		case EAssemblyComponentType::ECT_S_POMMEL:
			return &SmallPommel;
	}
	return nullptr;
}

bool UDagger::SetWeaponMode_Implementation(int Mode){
	return false;
}

float UDagger::GetWeaponRange_Implementation(){
	return 0.0f;
}

float UDagger::GetWeaponAttackDuration_Implementation(){
	return 0.0f;
}

float UDagger::GetWeaponAttackCooldown_Implementation(){
	return 0.0f;
}

bool UDagger::GetDamageStruct_Implementation(UPARAM(ref)FDamageStruct & Damage){
	return true;
}

bool UDagger::CanUseWeapon_Implementation(AAvatar * Avatar){
	return true;
}

bool UDagger::UseWeapon_Implementation(AAvatar * DamageCauser, UPARAM(ref)FDamageStruct & Damage, AActor * DamageTarget){

	return true;
}
