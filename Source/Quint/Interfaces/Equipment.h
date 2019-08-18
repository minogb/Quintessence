// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Tool.h"
#include "EquipmentStructure.h"
#include "ComponentStructure.h"
#include "UObject/Interface.h"
#include "Enumerations.h"
#include "Equipment.generated.h"
class UAssemblyComponent;

UINTERFACE(MinimalAPI)
class  UEquipmentInterface : public UInterface{
	GENERATED_BODY()
};

class QUINT_API IEquipmentInterface {
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent)
	EEquipmentSlot GetEquipmentSlot();
	virtual EEquipmentSlot GetEquipmentSlot_Implementation() { return EEquipmentSlot::ES_NONE; }
};
USTRUCT(BlueprintType)
struct FEquipmentBuildingStruct : public FTableRowBase {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEquipmentSlot EquipmentType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<EAssemblyComponentType> Components;
};
