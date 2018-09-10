// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemDataFunctionLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine.h"

UItemDataFunctionLibrary::UItemDataFunctionLibrary(){
	if (!ItemLookupTable) {
		static ConstructorHelpers::FObjectFinder<UDataTable> ItemTable(TEXT("DataTable'/Game/DataTables/ItemDataTable.ItemDataTable'"));
		if (ItemTable.Succeeded())
			ItemLookupTable = ItemTable.Object;
	}
}

bool UItemDataFunctionLibrary::GetItemStructFromId(int32 id, FItemDataStruct& ItemStruct) {
	FItemDataStruct* data = nullptr;
	if(ItemLookupTable)
		data = ItemLookupTable->FindRow<FItemDataStruct>(FName(*FString::FromInt(id)), ITEM_CONTEXT_STRING, false);
	ItemStruct = data ? *data : FItemDataStruct();
	return data != nullptr;
}

bool UItemDataFunctionLibrary::GetItemTypeEnumFromId(int32 id, TEnumAsByte<EItemTypeEnum>& itemType) {
	FItemDataStruct* data = nullptr;
	if(ItemLookupTable)
		data = ItemLookupTable->FindRow<FItemDataStruct>(FName(*FString::FromInt(id)), ITEM_CONTEXT_STRING, false);
	itemType = data ? data->ItemType: EItemTypeEnum();
	return data != nullptr;
}
