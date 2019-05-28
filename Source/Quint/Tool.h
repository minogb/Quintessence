// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Enumerations.h"
#include "Tool.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI)
class UTool : public UInterface
{
	GENERATED_BODY()
};

class QUINT_API ITool {

	GENERATED_BODY()
protected:
public:
	UFUNCTION(BlueprintNativeEvent)
	int GetHarvestLevelOfType(EHarvestType Type);

	virtual int GetHarvestLevelOfType_Implementation(EHarvestType Type);
};
