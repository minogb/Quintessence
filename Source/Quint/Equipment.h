// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "EquipmentStructure.h"
#include "Equipment.generated.h"

UCLASS()
class QUINT_API UEquipment : public UItem
{
	GENERATED_BODY()
	EEquipmentType Slot = EEquipmentType::ET_WEAPON;
public:
	UEquipment();
	virtual void Use(AActor* On) {};
	virtual TArray<bool> GetComponents() {return TArray<bool>();};
	EEquipmentType GetSlot() { return Slot; }
};
