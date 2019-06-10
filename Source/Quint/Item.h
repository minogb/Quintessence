// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Enumerations.h"
#include "Item.generated.h"



UCLASS(Blueprintable)
class QUINT_API UItem : public UObject
{
	GENERATED_BODY()
protected:
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
	int StackSize = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	int MaxStackSize = 2;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	int ItemTypeId = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
	int UniqueItemId = 1;
	TArray<EItemAction> Actions;
public:
	UItem();
	UPROPERTY(Replicated)
	uint32 bReplicatedFlag:1;
	UFUNCTION(BlueprintCallable)
	int GetTypeID(){return ItemTypeId;}
	UFUNCTION(BlueprintCallable)
	int GetUniqueID() { return UniqueItemId; }
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering")
	class UTexture2D* ImageTexture;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering")
	FColor Color;
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
