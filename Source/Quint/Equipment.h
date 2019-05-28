// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "EquipmentStructure.h"
#include "Equipment.generated.h"
class UEquipmentComponent;
UCLASS()
class QUINT_API UEquipment : public UItem
{
	GENERATED_BODY()
	EEquipmentType Slot = EEquipmentType::ET_WEAPON;
public:
	UEquipment();
	virtual void Use(AActor* On) {};
	virtual TArray<UEquipmentComponent> GetComponents();
	EEquipmentType GetSlot() { return Slot; }
};
