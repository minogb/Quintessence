// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ItemDataStruct.h"
#include "ItemDataFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class QUINT_API UItemDataFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	UItemDataFunctionLibrary();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static bool GetItemStructFromId(int32 id, FItemDataStruct& itemStruct);
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static bool GetItemTypeEnumFromId(int32 id, TEnumAsByte<EItemTypeEnum>& itemType);

};
