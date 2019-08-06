// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedWeaponBase.h"
#include "ProjectileBase.h"
#include "Avatar.h"
#include "Engine/GameEngine.h"
#include "Enumerations.h"
#include "Kismet/GameplayStatics.h"
#include "QuintPlayerController.h"

URangedWeaponBase::URangedWeaponBase() {
	//Setup defaults - to be changed on inherited classes
	Projectile = AProjectileBase::StaticClass();
	WeaponRange = 500;
	AttackDurationTime = .5;
	AttackCooldownTime = 1.f;
	AmoRequired = UItem::StaticClass();
}
bool URangedWeaponBase::CanUseWeapon_Implementation(AAvatar * Avatar){
	if(!IsValid(Avatar) && !IsValid(Avatar->GetQuintController()))
		return false;
	return IsValid(AmoRequired) ? Avatar->GetQuintController()->HasItem(AmoRequired, 1, EEquipmentSlot::ES_QUIVER) : true;
}

bool URangedWeaponBase::UseWeapon_Implementation(AAvatar * DamageCauser, UPARAM(ref)FDamageStruct & Damage, AActor * DamageTarget) {
	UWorld* world = GetWorld();
	if (world && CanUseWeapon_Implementation(DamageCauser) && IsValid(DamageCauser) && IsValid(DamageCauser->GetQuintController())
		&& (!IsValid(AmoRequired) || DamageCauser->GetQuintController()->ConsumeItem(AmoRequired,1,true, EEquipmentSlot::ES_QUIVER))) {
		
		FActorSpawnParameters params;
		params.Owner = DamageCauser;
		params.Instigator = DamageCauser;
		params.bNoFail = true;
		//Spawn the projectil delayed so we can set some values for it
		AProjectileBase* projectile = Cast<AProjectileBase>(UGameplayStatics::BeginDeferredActorSpawnFromClass(DamageCauser, Projectile, DamageCauser->GetTransform(),ESpawnActorCollisionHandlingMethod::AlwaysSpawn,DamageCauser->GetQuintController()));
		if (!projectile)
			return false;
		//like the target
		projectile->Target = DamageTarget;
		//And the damage to be applyed
		projectile->DamageStructure = Damage;
		UGameplayStatics::FinishSpawningActor(projectile, DamageCauser->GetTransform());
		return true;
	}
	return false;
}