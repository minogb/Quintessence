// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Interfaces/AssemblyInterface.h"
#include "Interfaces/Equipment.h"
#include "Interfaces/WeaponInterface.h"
#include "Dagger.generated.h"

/**
 * 
 */
UCLASS()
class QUINT_API UDagger : public UItem, public IAssemblyInterface, public IEquipmentInterface, public IWeaponInterface
{
	GENERATED_BODY()
	UPROPERTY()
	UItem* SmallBlade;
	UPROPERTY()
	UItem* ShortGrip;
	UPROPERTY()
	UItem* SmallPommel;
public:
	virtual UItem* GetComponent_Implementation(EAssemblyComponentType Type) override;
	virtual bool SetComponent_Implementation(UItem* Item) override;
};
