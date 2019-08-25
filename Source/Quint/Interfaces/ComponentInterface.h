// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "UObject/Interface.h"
#include "Enumerations.h"
#include "ComponentInterface.generated.h"
/**
 * 
 */
UINTERFACE(MinimalAPI)
class  UComponentInterface : public UInterface
{
	GENERATED_BODY()
};

class QUINT_API IComponentInterface {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	EAssemblyComponentType GetComponentSlot();
	virtual EAssemblyComponentType GetComponentSlot_Implementation() { return EAssemblyComponentType::ECT_NONE; }
};
