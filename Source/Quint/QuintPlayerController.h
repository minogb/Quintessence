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
	bool SetPlayerAvatar(class AAvatar* avatar);
protected:
	virtual void BeginPlay() override;
	class AAvatar* PlayerAvatar;
	//Player input needs to be passed to server
	void SetDestinationOrGoal();
	UFUNCTION(Server, Unreliable, WithValidation)
	void Server_SetDestination(FVector Location);
	//TODO: change bool action to an enum
	UFUNCTION(Server, Unreliable, WithValidation)
	void Server_SetGoalAndAction(AActor* Goal, bool Action);
};
