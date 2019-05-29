// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "EquipmentStructure.h"
#include "ComponentStructure.h"
#include "Equipment.generated.h"
class UEquipmentComponent;
UCLASS()
class QUINT_API UEquipment : public UItem
{
	GENERATED_BODY()
	EEquipmentType Slot = EEquipmentType::ET_WEAPON;
	TMap<EEquipmentComponentType, UEquipmentComponent*> Components;
public:
	UEquipment();
	virtual void Use(AActor* On) {};
	virtual TMap<EEquipmentComponentType, UEquipmentComponent*> GetComponents() {return Components;}
	virtual TArray<EEquipmentComponentType> GetRequiredComponentTypes();
	virtual bool InitComponents(TMap<EEquipmentComponentType, UEquipmentComponent*>& InitComponents);
	EEquipmentType GetSlot() { return Slot; }
};
