// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "Enumerations.h"
#include "ResourceNode.generated.h"


USTRUCT(BlueprintType)
struct FPlayerHarvestedStruct{
	GENERATED_BODY()
	//TODO: changed to something that can track the player
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Harvested Info")
	class AAvatar* Player;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Harvested Info")
	float TimeHarvested;
	FPlayerHarvestedStruct(class AAvatar* player, float time){
		Player= player;
		TimeHarvested = time;
	}
	FPlayerHarvestedStruct(){}
};
USTRUCT(BlueprintType)
struct FResourceReward{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Harvest Reward Info")
	TSubclassOf<UItem> ItemReward;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Harvest Reward Info")
	int MaxCount;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Harvest Reward Info")
	int MinCount;
	//Chance is 0-100
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Harvest Reward Info")
	int RewardChance;
	FResourceReward(TSubclassOf<UItem> reward, int max, int min=1, int Chance = 100){
		ItemReward = reward;
		MaxCount = FMath::Clamp(max, 1,100);
		MinCount = FMath::Clamp(min, 1,100);
		RewardChance = FMath::Clamp(Chance, 0,100);
	}
	FResourceReward(){}
};
UCLASS(BlueprintType)
class QUINT_API AResourceNode : public AActor, public IInteractable
{
	GENERATED_BODY()
	
protected:
	EHarvestType HarvestType;
	int HarvestLevel;
	/** The CapsuleComponent being used for movement collision (by CharacterMovement). Always treated as being vertically aligned in simple collision check functions. */
	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	class UBoxComponent* BoxComponent;
	UPROPERTY(Replicated)
	TArray<FPlayerHarvestedStruct>Harvesters;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Info", meta = (AllowPrivateAccess = "true"))
	TArray<FResourceReward>Rewards;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void RemovePlayersFromHarvesters();
	float TimeToReset = 4;
	void GivePlayerReward(class AAvatar* Player);
	TArray<class UItem*> GetPlayerReward(class AAvatar* Player);
	void SpawnWorldItem(class UItem* Item, AActor* ToOwn);
public:	
	// Sets default values for this actor's properties
	AResourceNode();
	virtual void HarvestThis(class AAvatar* Player);
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual bool CanPlayerHarvest(class AAvatar* Player);
	virtual int32 GetAvaliableTasks() override{ return Harvest | Examine; }
	virtual EInteractionType GetDefaultTask() override{ return Harvest; }
	virtual float GetSize() override;
	UFUNCTION(BlueprintCallable,BlueprintPure)
	TArray<FPlayerHarvestedStruct> GetHarvesters(){return Harvesters;}
	virtual bool IsValidTask(EInteractionType Task, class AAvatar* Player = nullptr);
};
