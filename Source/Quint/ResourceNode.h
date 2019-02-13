// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
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
UCLASS(BlueprintType)
class QUINT_API AResourceNode : public AActor, public IInteractable
{
	GENERATED_BODY()
	
protected:
	/** The CapsuleComponent being used for movement collision (by CharacterMovement). Always treated as being vertically aligned in simple collision check functions. */
	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	class UBoxComponent* BoxComponent;
	UPROPERTY(Replicated)
	TArray<FPlayerHarvestedStruct>Harvesters; 
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void RemovePlayersFromHarvesters();
	float TimeToReset = .1*60*60;
public:	
	// Sets default values for this actor's properties
	AResourceNode();
	virtual void HarvestThis(class AAvatar* Player);
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual int32 GetAvaliableTasks() override{ return Harvest | Examine; }
	virtual EInteractionType GetDefaultTask() override{ return Harvest; }
	virtual float GetSize() override;
	UFUNCTION(BlueprintCallable,BlueprintPure)
	TArray<FPlayerHarvestedStruct> GetHarvesters(){return Harvesters;}
	
};
