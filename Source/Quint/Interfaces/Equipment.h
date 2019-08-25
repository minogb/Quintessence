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
	int GetSkillLevel(ESkillType Skill);
	virtual int GetSkillLevel_Implementation(ESkillType Skill) { return 0; }

};