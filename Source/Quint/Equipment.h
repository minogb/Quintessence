// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Tool.h"
#include "EquipmentStructure.h"
#include "ComponentStructure.h"
#include "Equipment.generated.h"
class UEquipmentComponent;
UCLASS()
class QUINT_API UEquipment : public UItem, public ITool
{
	GENERATED_BODY()
	EEquipmentSlot Slot = EEquipmentSlot::ES_WEAPON;
	TMap<EEquipmentComponentType, UEquipmentComponent*> Components;
public:
	UDataTable* EquipmentDataTable;
	UEquipment();
	virtual void Use(AActor* On) {};
	virtual TMap<EEquipmentComponentType, UEquipmentComponent*> GetComponents() {return Components;}
	virtual TArray<EEquipmentComponentType> GetRequiredComponentTypes();
	//To be called after initial creation
	virtual bool InitComponents(FName EquipmentType, TMap<EEquipmentComponentType, UEquipmentComponent*>& InitComponents);
	EEquipmentSlot GetSlot() { return Slot; }
	virtual int GetHarvestLevelOfType_Implementation(EHarvestType Type);
};

USTRUCT(BlueprintType)
struct FEquipmentBuildingStruct : public FTableRowBase {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEquipmentSlot EquipmentType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<EEquipmentComponentType> Components;
};
