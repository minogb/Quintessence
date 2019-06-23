// Fill out your copyright notice in the Description page of Project Settings.


#include "CraftingInfo.h"

float UCraftingInfo::CalculateCraftingTime(){
	int requiredAmount = 0;
	for (FItemCraftingStruct Current : CraftingRecipe.Input) {
		requiredAmount += Current.Count;
	}
	return requiredAmount*.25;
}

void UCraftingInfo::InitObject(FCraftingStruct Recipe, int CraftingAmount){
	CraftingRecipe = Recipe;
	Amount = CraftingAmount;
	CraftingTime = CalculateCraftingTime();
}
