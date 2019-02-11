// Fill out your copyright notice in the Description page of Project Settings.

#include "QuintGameMode.h"
#include "PlayerVessel.h"
#include "QuintPlayerController.h"
#include "Engine/World.h"
#include "Avatar.h"
#include "PlayerVessel.h"
#include "Engine/GameEngine.h"
#include "QuintPlayerController.h"
AQuintGameMode::AQuintGameMode(){

	//PlayerControllerClass = AWorldController::StaticClass();
	DefaultPawnClass = APlayerVessel::StaticClass();
	PlayerControllerClass  = AQuintPlayerController::StaticClass();
}

void AQuintGameMode::PostLogin(APlayerController * NewPlayer){
	Super::PostLogin(NewPlayer);
	if(NewPlayer){
		if(GetWorld()){
			FActorSpawnParameters spawnInfo = FActorSpawnParameters();
			spawnInfo.Owner = NewPlayer;
			FVector location = FVector(-490.0,-86.44342,292.000671);
			AAvatar * avatar = nullptr;
			//todo: spawninfo set player name
			if(IsValid(PlayerAvatarClass)){
				avatar = GetWorld()->SpawnActor<AAvatar>(PlayerAvatarClass, location,FRotator(0),spawnInfo);
			}
			else{
				avatar = GetWorld()->SpawnActor<AAvatar>(location,FRotator(0),spawnInfo);
			}
			APlayerVessel* vessel = Cast<APlayerVessel>(NewPlayer->GetPawn());
			if(vessel){
				vessel->SetPlayerAvater(avatar,NewPlayer);
				AQuintPlayerController* player = Cast<AQuintPlayerController>(NewPlayer);
				if(player){
					player->SetPlayerAvatar(avatar);
				}
			}
		}
	}
}
