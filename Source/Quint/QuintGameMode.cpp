// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "QuintGameMode.h"
#include "PlayerCharacter.h"
#include "WorldController.h"
#include "UObject/ConstructorHelpers.h"

AQuintGameMode::AQuintGameMode()
{
	PlayerControllerClass = AWorldController::StaticClass();
	DefaultPawnClass = APlayerCharacter::StaticClass();
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/BpPlayerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	//PlayerStateClass = AQuintPlayerState::StaticClass();
}