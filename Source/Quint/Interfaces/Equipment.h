// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Tool.h"
#include "EquipmentStructure.h"
#include "ComponentStructure.h"
#include "UObject/Interface.h"
#include "Equipment.generated.h"
class UEquipmentComponent;

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
/*
UCLASS(Blueprintable)
class QUINT_API UEquipment : public UItem, public ITool
{
	GENERATED_BODY()
protected:
	EEquipmentSlot Slot = EEquipmentSlot::ES_WEAPON;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TMap<EEquipmentComponentType, UEquipmentComponent*>Components;
public:
	UDataTable* EquipmentDataTable;
	UEquipment();
	virtual void Use(AActor* On) {};
	//To be called after initial creation
	UFUNCTION(BlueprintCallable)
	bool InitComponents(TMap<EEquipmentComponentType, UEquipmentComponent*> InitComponents);
	//virtual bool InitComponents_Implementation(TMap<EEquipmentComponentType, UEquipmentComponent*> InitComponents);	
	virtual EEquipmentSlot GetEquipmentSlot_Implementation() { return Slot; }
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable,Blueprintpure)
	TMap<EEquipmentComponentType, UEquipmentComponent*> GetComponents();
	TMap<EEquipmentComponentType, UEquipmentComponent*> GetComponents_Implementation();

	virtual int GetHarvestLevelOfType_Implementation(EHarvestType Type);
	virtual int GetRequiredUseLevel_Implementation(EHarvestType Type);
};
*/
USTRUCT(BlueprintType)
struct FEquipmentBuildingStruct : public FTableRowBase {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEquipmentSlot EquipmentType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<EEquipmentComponentType> Components;
};
