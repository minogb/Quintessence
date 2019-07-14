// Fill out your copyright notice in the Description page of Project Settings.


#include "Enumerations.h"
#include "Item.h"
	//TODO: booster increases reward?
UItem* FLootStruct::GetReward(int booster) {
	UItem* reward = NewObject<UItem>(Reward);
	reward->SetStackSize(FMath::RandRange(MinReward, MaxReward));
	return reward;
}

void FDamageStruct::CollapseProbility(){
	//Do we glance?
	if (GlanceChance != 0 && FMath::RandRange(0, 1) > GlanceChance) {
		//Prevents a negitive range
		if (GlanceMultiplierFloor > GlanceMultiplierCeiling)
			GlanceMultiplierFloor = GlanceMultiplierCeiling;
		//Find range of Multiplier
		DamageAmount *= FMath::RandRange(GlanceMultiplierFloor, GlanceMultiplierCeiling);
		//set to 1 to signify that we did glance
		GlanceChance = 1;
	}
	//Do we crit?
	if (CritChance != 0 && FMath::RandRange(0, 1) > CritChance) {
		//Prevents a negitive range
		if (CritMultiplierFloor > CritMultiplierCeiling)
			CritMultiplierCeiling = CritMultiplierFloor;
		//Find range of Multiplier
		DamageAmount *= FMath::RandRange(CritMultiplierFloor, CritMultiplierCeiling);
		//set to 1 to signify that we did crit
		CritChance = 1;
	}
}
