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
	UPROPERTY(Replicated)
	class UItem* ItemReference;
	/** The CapsuleComponent being used for movement collision (by CharacterMovement). Always treated as being vertically aligned in simple collision check functions. */
	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComponent;
public:	
	// Sets default values for this actor's properties
	AItem_World();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void CombineWith(class UItem*& item);
	
	virtual int32 GetAvaliableTasks() override{ return Pick_Up | Examine; }
	virtual EInteractionType GetDefaultTask() override{ return Pick_Up; }
	
};
