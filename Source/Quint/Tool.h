// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipment.h"
#include "HarvestTypeEnum.h"
#include "Tool.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class QUINT_API UTool : public UEquipment{

	GENERATED_BODY()
protected:
	TMap<EHarvestType, int>HarvestLevels;
public:
	UTool();
	int GetHarvestLevelOfType(EHarvestType Type);
};
