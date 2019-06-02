// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Tool.h"
#include "EquipmentStructure.h"
#include "ComponentStructure.h"
#include "Equipment.generated.h"
class UEquipmentComponent;
UCLASS(Blueprintable)
class QUINT_API UEquipment : public UItem
{
	GENERATED_BODY()
	EEquipmentSlot Slot = EEquipmentSlot::ES_WEAPON;
public:
	UDataTable* EquipmentDataTable;
	UEquipment();
	virtual void Use(AActor* On) {};
	//To be called after initial creation
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool InitComponents(TMap<EEquipmentComponentType, UEquipmentComponent*> InitComponents);
	virtual bool InitComponents_Implementation(TMap<EEquipmentComponentType, UEquipmentComponent*> InitComponents);	EEquipmentSlot GetSlot() { return Slot; }
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	TMap<EEquipmentComponentType, UEquipmentComponent*> GetComponents();
	TMap<EEquipmentComponentType, UEquipmentComponent*> GetComponents_Implementation();
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
