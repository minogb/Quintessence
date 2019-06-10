// Fill out your copyright notice in the Description page of Project Settings.


#include "Enumerations.h"
#include "Item.h"
	//TODO: booster increases reward?
UItem* FLootStruct::GetReward(int booster) {
	UItem* reward = NewObject<UItem>(Reward);
	reward->SetStackSize(FMath::RandRange(MinReward, MaxReward));
	return reward;
}