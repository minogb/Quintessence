// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Assemblies/AssembledEquipment.h"
#include "Interfaces/WeaponInterface.h"
#include "Halberd.generated.h"

/**
 * 
 */
UCLASS()
class QUINT_API UHalberd : public UAssembledEquipment, public IWeaponInterface
{
	GENERATED_BODY()

	UPROPERTY()
	UItem* AxeHead;
	UPROPERTY()
	UItem* Spike;
	UPROPERTY()
	UItem* LongGrip;
	UPROPERTY()
	UItem* LongHandle;
public:
	UHalberd();
	virtual FString GetSaveJSON() override;
	virtual UItem** GetComponent(EAssemblyComponentType Type);
	virtual void InitWithJson(TSharedPtr<FJsonObject> JsonData) override;

	virtual int GetSkillLevel_Implementation(ESkillType Skill) { return 0; }

	virtual bool SetWeaponMode_Implementation(int Mode = 0);
	virtual float GetWeaponRange_Implementation();
	virtual float GetWeaponAttackDuration_Implementation();
	virtual float GetWeaponAttackCooldown_Implementation();
	virtual bool GetDamageStruct_Implementation(UPARAM(ref)FDamageStruct& Damage);
	virtual bool CanUseWeapon_Implementation(AAvatar* Avatar);
	virtual bool UseWeapon_Implementation(AAvatar* DamageCauser, UPARAM(ref)FDamageStruct& Damage, AActor* DamageTarget);
};
