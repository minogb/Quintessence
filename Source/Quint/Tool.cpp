// Fill out your copyright notice in the Description page of Project Settings.


#include "Tool.h"

int ITool::GetHarvestLevelOfType_Implementation(EHarvestType Type) {
	TMap<EHarvestType, int>HarvestLevels;
	HarvestLevels.Add(EHarvestType::HT_MINING, 1);
	return HarvestLevels.Contains(Type) ? HarvestLevels[Type] : 0;
}