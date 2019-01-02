// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interactable.h"
#include "Avatar.generated.h"

#define ECC_Interactable ECC_GameTraceChannel1
UCLASS()
class QUINT_API AAvatar : public ACharacter, public IInteractable{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	// Sets default values for this character's properties
	AAvatar();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual int32 GetAvaliableTasks() { return Follow | Trade | Examine; }
	
	
};
