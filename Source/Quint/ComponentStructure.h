// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EAssemblyComponentType : uint8 {
	ECT_NONE UMETA(DisplayName = "Invalid Component"),
	ECT_S_BLADE UMETA(DisplayName = "Short Blade Component"),
	ECT_M_BLADE UMETA(DisplayName = "Medium Blade Component"),
	ECT_L_BLADE UMETA(DisplayName = "Large Blade Component"),
	ECT_XL_BLADE UMETA(DisplayName = "XL Blade Component"),
	ECT_HAMMER_HEAD UMETA(DisplayName = "Hammer Head Component"),
	ECT_AXE_HEAD UMETA(DisplayName = "Axe Head Component"),
	ECT_PICK_AXE_HEAD UMETA(DisplayName = "Pick Axe Head Component"),
	ECT_S_POMMEL UMETA(DisplayName = "Small Pommel Component"),
	ECT_M_POMMEL UMETA(DisplayName = "Medium Pommel Component"),
	ECT_L_POMMEL UMETA(DisplayName = "Large Pommel Component"),
	ECT_S_GRIP UMETA(DisplayName = "Small Grip Component"),
	ECT_M_GRIP UMETA(DisplayName = "Medium Grip Component"),
	ECT_L_GRIP UMETA(DisplayName = "Large Grip Component"),
	ECT_GUARD UMETA(DisplayName = "Gaurd Component"),
	ECT_S_HANDLE UMETA(DisplayName = "Small Handle Component"),
	ECT_M_HANDLE UMETA(DisplayName = "Medium Handle Component"),
	ECT_L_HANDLE UMETA(DisplayName = "Large Handle Component")
};