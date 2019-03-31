// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"



UCLASS(Blueprintable)
class QUINT_API UItem : public UObject
{
	GENERATED_BODY()
private:
	UPROPERTY(Replicated)
	int StackSize = 1;
	int MaxStackSize = 1;
	int ItemId = 1;
public:
	UPROPERTY(Replicated)
	uint32 bReplicatedFlag:1;
	UFUNCTION(BlueprintCallable)
	int GetID(){return ItemId;}
	
	UFUNCTION(BlueprintCallable)
	int GetStackSize(){return StackSize;}

	UFUNCTION(BlueprintCallable)
	int GetMaxStackSize(){return MaxStackSize;}

	void Combine(UItem*& that);
	virtual bool IsSupportedForNetworking() const override{return true;}
	void SetStackSize(int Amount){StackSize = Amount <= MaxStackSize ? Amount : MaxStackSize;}
};

USTRUCT(BlueprintType)
struct FLootStruct{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UItem> Reward;
	//Range from 0 to 1. if 0 always
	UPROPERTY(EditAnywhere)
	float ChancePercent;
	UPROPERTY(EditAnywhere)
	int MinReward;
	UPROPERTY(EditAnywhere)
	int MaxReward;
	FLootStruct(){
		MinReward = 1;
		MaxReward = 1;
		ChancePercent = 0;
	}
	//TODO: booster increases reward?
	UItem* GetReward(int booster = 0){
		UItem* reward =  NewObject<UItem>(Reward);
		reward->SetStackSize(FMath::RandRange(MinReward,MaxReward));
		return reward;
	}
};