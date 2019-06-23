// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Enumerations.h"
#include "CraftingInfo.generated.h"

/**
 * 
 */
UCLASS()
class QUINT_API UCraftingInfo : public UObject {
	GENERATED_BODY()
	int Amount;
	FCraftingStruct CraftingRecipe;
	float CraftingTime;
	float CalculateCraftingTime();
public:
	UFUNCTION(BlueprintCallable)
	void InitObject(FCraftingStruct Recipe, int CraftingAmount);
	UFUNCTION(BlueprintCallable)
	FCraftingStruct	GetCraftingRecipe() { return CraftingRecipe; }
	UFUNCTION(BlueprintCallable)
	int	GetCraftingAmount() { return Amount; }
	UFUNCTION(BlueprintCallable)
	float GetCraftTime() { return CraftingTime; }
	void DecrimentCraftingAmount() { Amount--; }
};
