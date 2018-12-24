// Fill out your copyright notice in the Description page of Project Settings.

#include "QuintPlayerController.h"
#include "Engine/World.h"
#include "Avatar.h"
#include "PlayerVessel.h"
AQuintPlayerController::AQuintPlayerController(){
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

}

void AQuintPlayerController::BeginPlay(){
	if(HasAuthority()){
		if(GetWorld()){
			FActorSpawnParameters spawnInfo = FActorSpawnParameters();
			FVector location = FVector(-490.0,-86.44342,292.000671);
			//todo: spawninfo set player name
			AAvatar* avatar = GetWorld()->SpawnActor<AAvatar>(location,FRotator(0),spawnInfo);
			APlayerVessel* vessel = Cast<APlayerVessel>(GetPawn());
			if(vessel){
				vessel->SetPlayerAvater(avatar,this);
			}
		}
	}
}
