// Fill out your copyright notice in the Description page of Project Settings.

#include "QuintPlayerController.h"
#include "Engine/World.h"
#include "Avatar.h"
AQuintPlayerController::AQuintPlayerController(){
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

}

void AQuintPlayerController::BeginPlay(){
	if(HasAuthority()){
		if(GetWorld()){
			FActorSpawnParameters spawnInfo;
			//todo: spawninfo set player name
			GetWorld()->SpawnActor<AAvatar>(GetPawn()->GetActorLocation(),GetPawn()->GetActorRotation(),spawnInfo);
		}
	}
}
