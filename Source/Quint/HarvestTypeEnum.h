// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EHarvestType : uint8 {
	HT_NONE UMETA(DisplayName = "NONE"),
	HT_MINING UMETA(DisplayName = "MINING")
};