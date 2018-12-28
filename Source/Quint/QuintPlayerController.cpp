// Fill out your copyright notice in the Description page of Project Settings.

#include "QuintPlayerController.h"
#include "Engine/World.h"
#include "Avatar.h"
#include "PlayerVessel.h"
AQuintPlayerController::AQuintPlayerController(){
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

}

bool AQuintPlayerController::SetPlayerAvatar(AAvatar * avatar)
{
	return false;
}

void AQuintPlayerController::BeginPlay(){
}

void AQuintPlayerController::SetDestinationOrGoal(){
	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	if(GetHitResultUnderCursor(ECC_Visibility, false, Hit)){
		float const Distance = FVector::Dist(Hit.Location, GetPawn()->GetActorLocation());
		// We hit something, move there
		//if (Hit.Actor.Get() || Distance > GetMinRange())
			//SetNewMoveDestination(Hit.ImpactPoint, Hit.Actor.Get());
		//TODO: Change avatar here to any interactble
		if(Hit.Actor.Get() && Cast<AAvatar>(Hit.Actor.Get())){
			Server_SetGoalAndAction(Hit.Actor.Get(), true);
		}
		else{
			Server_SetDestination(Hit.ImpactPoint);
		}
	}
}

void AQuintPlayerController::Server_SetDestination_Implementation  (FVector Location){

}
void AQuintPlayerController::Server_SetGoalAndAction_Implementation  (AActor * Goal, bool Action){

}

bool AQuintPlayerController::Server_SetDestination_Validate (FVector Location){
	return true;
}
bool AQuintPlayerController::Server_SetGoalAndAction_Validate (AActor * Goal, bool Action){
	return true;
}