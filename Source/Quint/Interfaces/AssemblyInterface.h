// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "UObject/Interface.h"
#include "Enumerations.h"
#include "AssemblyInterface.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI)
class  UAssemblyInterface : public UInterface
{
	GENERATED_BODY()
};

class QUINT_API IAssemblyInterface {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UItem* GetComponent(EAssemblyComponentType Type);
	virtual UItem* GetComponent_Implementation(EAssemblyComponentType Type) { return nullptr; }
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool SetComponent(UItem* Component);
	virtual bool SetComponent_Implementation(UItem* Component) { return false; }
};
