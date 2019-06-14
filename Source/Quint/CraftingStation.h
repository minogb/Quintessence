// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "CraftingStation.generated.h"

UCLASS()
class QUINT_API ACraftingStation : public AActor, public IInteractable
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<class UUserWidget> WidgetClass;
public:	
	/** The CapsuleComponent being used for movement collision (by CharacterMovement). Always treated as being vertically aligned in simple collision check functions. */
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxComponent;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Sets default values for this actor's properties
	ACraftingStation();
	virtual bool UseThis_Implementation(UObject* With, UObject* Source = nullptr) override;
	virtual float GetSize_Implementation() override;
	virtual EInteractionType GetDefaultTask_Implementation() override;
	virtual bool IsValidTask_Implementation(TEnumAsByte<EInteractionType> Task, class AAvatar* Player = nullptr);

};
