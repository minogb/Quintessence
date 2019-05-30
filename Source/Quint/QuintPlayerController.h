// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interactable.h"
#include "Enumerations.h"
#include "EquipmentStructure.h"
#include "QuintPlayerController.generated.h"
#define ECC_Interactable ECC_GameTraceChannel1
#define ECC_Floor ECC_GameTraceChannel2

UCLASS()
class QUINT_API AQuintPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	int InventorySizeMax = 30;
	UPROPERTY(Replicated)
	TArray<class UItem*> Inventory;
	UPROPERTY(Replicated)
	FEquipmentStruct Equipment;
	UPROPERTY(Replicated)
	class AAvatar* PlayerAvatar;
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	//Player input needs to be passed to server
	void SetDestinationOrGoal();
	bool IsValidLocation(FVector location);
	UFUNCTION(Server, Unreliable, WithValidation)
	void Server_SetDestination(FVector Location);
	UFUNCTION(Server, Unreliable, WithValidation)
	void Server_SetGoalAndAction(AActor* Goal, EInteractionType Action);
	int GetIndexOfItem(UItem* Item);
public:
	AQuintPlayerController();
	virtual bool ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags) override;
	bool SetPlayerAvatar(class AAvatar* avatar);

	UFUNCTION(BlueprintCallable)
	void DoItemAction(UItem* Item, EItemAction Action);

	UFUNCTION(Server, Reliable, WithValidation,BlueprintCallable)
	void EquipItem(int Slot);
	void EquipItem_Implementation(int Slot);
	bool EquipItem_Validate(int Slot);

	void EquipItem(UItem* Item);
	UFUNCTION(Server, Reliable, WithValidation,BlueprintCallable)
	void UnEquipItem(EEquipmentSlot Slot);
	void UnEquipItem_Implementation(EEquipmentSlot Slot);
	bool UnEquipItem_Validate(EEquipmentSlot Slot);

	void UnEquipItem(UItem* Item);


	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
	void DropItem(int Slot);
	void DropItem_Implementation(int Slot);
	bool DropItem_Validate(int Slot);

	void DropItem(UItem* Item);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetHighestToolLevelOfType(EHarvestType Type);
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetEquipmentToolLevelOfType(EHarvestType Type);
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UEquipment* GetEquipment(EEquipmentSlot EquipmentType);
	void AddItemToInventory(class AItem_World* ItemWorld);
	void AddItemToInventory(class UItem*& Item);
	UFUNCTION(BlueprintCallable,BlueprintPure)
	int GetInventorySize(){return InventorySizeMax;}
	UFUNCTION(BlueprintCallable,BlueprintPure)
	class UItem* GetInventorySlot(int index){return Inventory.IsValidIndex(index)? Inventory[index] : nullptr;}
	UFUNCTION(BlueprintCallable,BlueprintPure)
	class AAvatar* GetPlayerAvatar(){return PlayerAvatar;}
};
