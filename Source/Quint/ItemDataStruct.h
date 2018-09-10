// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "Engine/DataTable.h"
#include "Engine/Texture2D.h"
#include "ItemDataStruct.generated.h"

/**
 * 
 */
static UDataTable* ItemLookupTable = nullptr;
static const FString ITEM_CONTEXT_STRING(TEXT("GENERAL"));
UENUM(BlueprintType)
enum EItemTypeEnum {
	//Can be attacked without consiquince
	No_Item_Type UMETA(DisplayName = "No Type"),
	//cannot be attacked
	Weapon_Item_Type UMETA(DisplayName = "Weapon Type")
};
USTRUCT(Blueprintable)
struct QUINT_API FItemDataStruct : public FTableRowBase
{
	GENERATED_BODY()
	//name of the item
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FString Name = "N/A";
	//describe the item
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FString Description = "N/A";
	//describe the item
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UTexture2D* Image;
	//max stack size of the item. Is this the best spot for this?
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int32 MaxStackSize = 1;
	//the sub data table to use to find more info
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TEnumAsByte<EItemTypeEnum> ItemType = No_Item_Type;
};
