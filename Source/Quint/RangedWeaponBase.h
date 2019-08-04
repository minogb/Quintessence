// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h" 
#include "Interfaces/Equipment.h"
#include "Interfaces/WeaponInterface.h"
#include "RangedWeaponBase.generated.h"

/**
 * 
 */
UCLASS()
class QUINT_API URangedWeaponBase : public UItem, public IEquipmentInterface, public IWeaponInterface
{
	GENERATED_BODY()
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AProjectileBase> Projectile;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	float WeaponRange;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	float AttackDurationTime;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	float AttackCooldownTime;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	FDamageStruct DamageStructure;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UItem> AmoRequired;
public:
	URangedWeaponBase();
	virtual float GetWeaponRange_Implementation() override { return WeaponRange; };
	virtual float GetWeaponAttackDuration_Implementation() override { return AttackDurationTime; };
	virtual float GetWeaponAttackCooldown_Implementation() override { return AttackCooldownTime; };
	virtual bool GetDamageStruct_Implementation(UPARAM(ref)FDamageStruct& Damage) override { Damage = DamageStructure; return true; };
	virtual bool CanUseWeapon_Implementation(AAvatar* Avatar) override;
	virtual bool UseWeapon_Implementation(AAvatar* DamageCauser, UPARAM(ref)FDamageStruct& Damage, AActor* DamageTarget) override;
	virtual EEquipmentSlot GetEquipmentSlot_Implementation() override { return EEquipmentSlot::ES_WEAPON; }
};
