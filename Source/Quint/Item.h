// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Enumerations.h"
#include "Engine/Texture2D.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Engine/DataTable.h"
#include "Item.generated.h"



USTRUCT(BlueprintType)
struct FItemIndex : public FTableRowBase {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadonly)
	FString ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadonly)
	TSubclassOf<class UItem> ItemClass;
	UPROPERTY(EditAnywhere, BlueprintReadonly)
	class UTexture2D* ImageTexture;

};

UCLASS(Blueprintable)
class QUINT_API UItem : public UObject
{
	friend class AQuintPlayerController;
	GENERATED_BODY()
protected:
	static UDataTable* DataTable;

	bool WaitingOrHasID = false;

	UPROPERTY(Replicated, BlueprintReadOnly)
	int StackSize = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Info")
	int MaxStackSize = 1;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Info")
	int ItemTableID = 0;

	int UniqueItemId = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Info")
	int CraftExperience = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering")
	FColor Color;

	TArray<EItemAction> Actions;
	//On creation
	void OnItemDataRecived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	UFUNCTION(BlueprintCallable)
	void InitItemID();

public:
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
	AActor* Owner;
	UPROPERTY(Replicated)
	uint32 bReplicatedFlag : 1;

	UItem();
	//Load data from json. if has nested items, this is where it is loaded in
	virtual void InitWithJson(TSharedPtr<FJsonObject> JsonData);

	virtual FString GetSaveJSON();

	UFUNCTION(BlueprintCallable)
	int GetTypeID(){return ItemTableID;}

	UFUNCTION(BlueprintCallable)
	int GetUniqueID() { return UniqueItemId; }

	UFUNCTION(BlueprintCallable)
	int GetStackSize(){return StackSize;}

	UFUNCTION(BlueprintCallable)
	int GetMaxStackSize(){return MaxStackSize;}

	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<EItemAction> GetCustomInventoryOptions() {return Actions;}

	void Combine(UItem*& that);

	virtual bool IsSupportedForNetworking() const override{return true;}

	UFUNCTION(BlueprintCallable)
	void SetStackSize(int Amount){ StackSize = Amount <= MaxStackSize ? (Amount > 0 ? Amount : 0) : MaxStackSize;}

	static UItem* CreateItemFromTable(int TableID, AActor* Owner, TSharedPtr<FJsonObject> JsonData = nullptr);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static bool GetItemIndex(int TableID, FItemIndex& Result);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static bool GetItemIndexFromSubclass(TSubclassOf<UItem> ItemClass, FItemIndex& Result);
};