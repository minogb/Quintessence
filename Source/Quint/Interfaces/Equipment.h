// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Tool.h"
#include "EquipmentStructure.h"
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
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	EEquipmentSlot GetEquipmentSlot();
	virtual EEquipmentSlot GetEquipmentSlot_Implementation() { return EEquipmentSlot::ES_NONE; }

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	TArray<FSkillLevelStruct> GetSkillsRequired();
	virtual TArray<FSkillLevelStruct> GetSkillsRequired_Implementation(){ return TArray<FSkillLevelStruct>(); }

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool CanPlayerEquip(AAvatar* Player);
	virtual bool CanPlayerEquip_Implementation(AAvatar* Player) { return false; }

};