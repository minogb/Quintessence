// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "EquipmentStructure.generated.h"

/**
 * 
 */
class UEquipment;
UENUM(BlueprintType, Meta = (Bitflags))
enum class EEquipmentSlot : uint8 {
	ES_NONE UMETA(DisplayName = "None"),
	ES_HELM UMETA(DisplayName = "Helm"),
	ES_CHEST UMETA(DisplayName = "Chest"),
	ES_LEGGINGS UMETA(DisplayName = "Leggings"),
	ES_BOOTS UMETA(DisplayName = "Boots"),
	ES_GLOVES UMETA(DisplayName = "Gloves"),
	ES_QUIVER UMETA(DisplayName = "Quiver"),
	ES_SHEILD UMETA(DisplayName = "Sheild"),
	ES_RING UMETA(DisplayName = "Ring"),
	ES_WEAPON UMETA(DisplayName = "Weapon")
};
USTRUCT(BlueprintType)
struct FEquipmentStruct  {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Helm")
	UEquipment* Helm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chest")
	UEquipment* Chest;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Leggings")
	UEquipment* Leggings;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boots")
	UEquipment* Boots;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gloves")
	UEquipment* Gloves;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	UEquipment* Weapon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sheild")
	UEquipment* Sheild;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quiver")
	UEquipment* Quiver;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ring")
	UEquipment* Ring;
	UEquipment* SetEquipment(UEquipment* Equipment, EEquipmentSlot Slot = EEquipmentSlot::ES_NONE);
	UEquipment* Get(EEquipmentSlot Slot);
};
