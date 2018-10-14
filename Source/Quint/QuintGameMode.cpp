// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "QuintGameMode.h"
#include "PlayerCharacter.h"
#include "WorldController.h"
#include "UObject/ConstructorHelpers.h"

AQuintGameMode::AQuintGameMode()
{
	PlayerControllerClass = APlayerCharacter::StaticClass();
	DefaultPawnClass = APlayerCharacter::StaticClass();
	//PlayerStateClass = AQuintPlayerState::StaticClass();
}