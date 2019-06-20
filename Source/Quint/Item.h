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

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
	int StackSize = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
	int MaxStackSize = 2;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
	int IndexId = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
	int UniqueItemId = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
	FString ItemName = "Item";
	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Info")
	UTexture2D* ImageTexture;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering")
	FColor Color;
	TArray<EItemAction> Actions;
public:
	UItem();
	UPROPERTY(Replicated)
	uint32 bReplicatedFlag:1;
	UFUNCTION(BlueprintCallable)
	int GetTypeID(){return IndexId;}
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
	void SetStackSize(int Amount){StackSize = Amount <= MaxStackSize ? Amount : MaxStackSize;}
	static UItem* CREATE_ITEM(AActor* Outer, TSubclassOf<UItem> SubClass, int Amount);
};