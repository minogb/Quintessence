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
}
