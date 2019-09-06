// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Assemblies/AssembledEquipment.h"
#include "Interfaces/WeaponInterface.h"
#include "BroadSword.generated.h"

/**
 * 
 */
UCLASS()
class QUINT_API UBroadSword : public UAssembledEquipment, public IWeaponInterface
{
	GENERATED_BODY()
	UPROPERTY()
	UItem* HeavyBlade;
	UPROPERTY()
	UItem* Pommel;
	UPROPERTY()
	UItem* LongGrip;
	UPROPERTY()
	UItem* Guard;

public:
	UBroadSword();
	virtual UItem** GetComponent(EAssemblyComponentType Type) override;

	virtual int GetSkillLevel_Implementation(ESkillType Skill) { return 0; }

	virtual bool SetWeaponMode_Implementation(int Mode = 0);
	virtual float GetWeaponRange_Implementation();
	virtual float GetWeaponAttackDuration_Implementation();
	virtual float GetWeaponAttackCooldown_Implementation();
	virtual bool GetDamageStruct_Implementation(UPARAM(ref)FDamageStruct& Damage);
	virtual bool CanUseWeapon_Implementation(AAvatar* Avatar);
	virtual bool UseWeapon_Implementation(AAvatar* DamageCauser, UPARAM(ref)FDamageStruct& Damage, AActor* DamageTarget);
	
};
