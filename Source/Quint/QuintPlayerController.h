// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "QuintPlayerController.generated.h"
#define ECC_Interactable ECC_GameTraceChannel1
#define ECC_Floor ECC_GameTraceChannel2

UCLASS()
class QUINT_API AQuintPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AQuintPlayerController();
	bool SetPlayerAvatar(class AAvatar* avatar);
protected:
	class AAvatar* PlayerAvatar;
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	//Player input needs to be passed to server
	void SetDestinationOrGoal();
	bool IsValidLocation(FVector location);
	UFUNCTION(Server, Unreliable, WithValidation)
	void Server_SetDestination(FVector Location);
	//TODO: change bool action to an enum
	UFUNCTION(Server, Unreliable, WithValidation)
	void Server_SetGoalAndAction(AActor* Goal, bool Action);
};
