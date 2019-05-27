// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EquipmentStructure.generated.h"

/**
 * 
 */
class UEquipment;
UENUM(BlueprintType, Meta = (Bitflags))
enum class EEquipmentType : uint8 {
	ET_NONE UMETA(DisplayName = "None"),
	ET_HELM UMETA(DisplayName = "Helm"),
	ET_CHEST UMETA(DisplayName = "Chest"),
	ET_LEGGINGS UMETA(DisplayName = "Leggings"),
	ET_BOOTS UMETA(DisplayName = "Boots"),
	ET_GLOVES UMETA(DisplayName = "Gloves"),
	ET_QUIVER UMETA(DisplayName = "Quiver"),
	ET_SHEILD UMETA(DisplayName = "Sheild"),
	ET_RING UMETA(DisplayName = "Ring"),
	ET_WEAPON UMETA(DisplayName = "Weapon")
};
USTRUCT(BlueprintType)
struct FEquipmentStruct {
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
	UEquipment* SetEquipment(UEquipment* Equipment, EEquipmentType Slot = EEquipmentType::ET_NONE);
	UEquipment* Get(EEquipmentType Slot);
};