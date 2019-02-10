// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class QUINT_API UItem : public UObject
{
	GENERATED_BODY()
private:
	UPROPERTY(Replicated)
	int StackSize = 1;
	int MaxStackSize = 5;
	int ItemId = 1;
public:
	UFUNCTION(BlueprintCallable)
	int GetID(){return ItemId;}
	
	UFUNCTION(BlueprintCallable)
	int GetStackSize(){return StackSize;}

	UFUNCTION(BlueprintCallable)
	int GetMaxStackSize(){return MaxStackSize;}

	void Combine(UItem*& that);
};
