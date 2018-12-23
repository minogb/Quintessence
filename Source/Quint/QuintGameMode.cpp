// Fill out your copyright notice in the Description page of Project Settings.

#include "QuintGameMode.h"
#include "PlayerVessel.h"
#include "QuintPlayerController.h"
AQuintGameMode::AQuintGameMode(){

	//PlayerControllerClass = AWorldController::StaticClass();
	DefaultPawnClass = APlayerVessel::StaticClass();
	PlayerControllerClass  = AQuintPlayerController::StaticClass();
}