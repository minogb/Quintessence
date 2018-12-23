// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "QuintPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class QUINT_API AQuintPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AQuintPlayerController();
protected:
	virtual void BeginPlay() override;
};
