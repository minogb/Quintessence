// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "Item_World.generated.h"


UCLASS()
class QUINT_API AItem_World : public AActor, public IInteractable
{
	GENERATED_BODY()
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	/** The CapsuleComponent being used for movement collision (by CharacterMovement). Always treated as being vertically aligned in simple collision check functions. */
	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	class UBoxComponent* BoxComponent;
public:	
	// Sets default values for this actor's properties
	AItem_World();
	UPROPERTY(Replicated, Category = "Item", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UItem* ItemReference = NULL;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void CombineWith(class UItem*& item);
	UFUNCTION(BlueprintCallable)
	void InitItem(class UItem* item);
	virtual uint8 GetAvaliableTasks_Implementation() override{ return (uint8)EInteractionType::Pick_Up | (uint8)EInteractionType::Examine; }
	virtual EInteractionType GetDefaultTask_Implementation() override{ return EInteractionType::Pick_Up; }
	
};
