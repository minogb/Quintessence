// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Enumerations.h"
#include "Engine/Texture2D.h"
#include "Item.generated.h"



USTRUCT(BlueprintType)
struct FItemIndex {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	FString ItemName;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UItem> ItemClass;
	UPROPERTY(EditAnywhere)
	class UTexture2D* ImageTexture;

};

USTRUCT(BlueprintType)
struct FTextureStruct : public FTableRowBase {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadonly)
	UTexture2D* ImageTexture;
};
UCLASS(Blueprintable)
class QUINT_API UItem : public UObject
{
	GENERATED_BODY()
protected:
	       
	UPROPERTY(Replicated, BlueprintReadOnly)
	int StackSize = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Info")
	int MaxStackSize = 1;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Info")
	int ItemTableID = 1;

	int UniqueItemId = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Info")
	FString ItemName = "Item";

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Info")
	UTexture2D* ImageTexture;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Info")
	int CraftExperience = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering")
	FColor Color;

	TArray<EItemAction> Actions;

public:
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
	UObject* Owner;
	UPROPERTY(Replicated)
	uint32 bReplicatedFlag : 1;

	UItem();

	FString GetSaveJSON();

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
	static UItem* CREATE_ITEM(AActor* Outer, TSubclassOf<UItem> SubClass, int Amount);
};