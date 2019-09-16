// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "EquipmentStructure.generated.h"

class UItem;
/**
 * 
 */
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
	UItem* Helm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chest")
	UItem* Chest;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Leggings")
	UItem* Leggings;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boots")
	UItem* Boots;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gloves")
	UItem* Gloves;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	UItem* Weapon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sheild")
	UItem* Sheild;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quiver")
	UItem* Quiver;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ring")
	UItem* Ring;

	FString GetSaveJSON();
	void InitWithJSON(TSharedPtr<FJsonObject> InventoryJSON);
	UItem* SetEquipment(UItem* Equipment, EEquipmentSlot Slot = EEquipmentSlot::ES_NONE);
	UItem* Get(EEquipmentSlot Slot);
	TArray<UItem*> GetAsList();
};
	