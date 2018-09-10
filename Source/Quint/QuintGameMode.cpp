// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "QuintGameMode.h"
#include "QuintPlayerController.h"
#include "QuintCharacter.h"
#include "QuintPlayerState.h"
#include "WeaponDataStruct.h"
#include "UObject/ConstructorHelpers.h"

AQuintGameMode::AQuintGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AQuintPlayerController::StaticClass();
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/QuintPlayerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	PlayerStateClass = AQuintPlayerState::StaticClass();
}