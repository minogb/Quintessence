// Fill out your copyright notice in the Description page of Project Settings.

#include "Interactable.h"
#include "Item.h"
TArray<UItem*> IInteractable::GetLootRewards(TArray<FLootStruct>LootTable){
	TArray<UItem*> Rewards;
	for(int i = 0; i <LootTable.Num(); i++){
		if(LootTable.IsValidIndex(i)){
			float chance = FMath::RandRange(0,1);
			if(LootTable[i].ChancePercent <= chance){
				Rewards.Add(LootTable[i].GetReward());
			}
		}
	}
	return Rewards;
}