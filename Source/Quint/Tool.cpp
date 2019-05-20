// Fill out your copyright notice in the Description page of Project Settings.


#include "Tool.h"


UTool::UTool() {
	HarvestLevels.Add(EHarvestType::HT_MINING, 1);
}

int UTool::GetHarvestLevelOfType(EHarvestType Type) {
	return HarvestLevels.Contains(Type) ? HarvestLevels[Type] : 0;
}