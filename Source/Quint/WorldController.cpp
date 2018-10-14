// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldController.h"
#include "PawnInterface.h"
#include "GameFramework/Pawn.h"


AWorldController::AWorldController(){
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

}

void AWorldController::BeginPlay(){
	Super::BeginPlay();
}

void AWorldController::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
}

IPawnInterface* AWorldController::GetPlayerPawn(){
	return Cast<IPawnInterface>(GetPawn());
}
void AWorldController::SetupInputComponent(){
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AWorldController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AWorldController::OnSetDestinationReleased);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AWorldController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AWorldController::MoveToTouchLocation);

}


void AWorldController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location){
	FVector2D ScreenSpaceLocation(Location);
	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	SetDestinationHelper(HitResult);
}

void AWorldController::OnSetDestinationPressed(){
}

void AWorldController::OnSetDestinationReleased(){
	// Trace to see what is under the mouse cursor
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	SetDestinationHelper(HitResult);
}

void AWorldController::SetDestinationHelper(FHitResult HitResult){
	SetNewMoveDestination(HitResult.ImpactPoint, HitResult.Actor.Get());
}

void AWorldController::SetNewMoveDestination_Implementation(const FVector DestLocation, AActor* DestActor){
	IPawnInterface* PawnInterface = GetPlayerPawn();
	//pass the command onto the pawn
	if(PawnInterface){
		PawnInterface->MovePawnToLocationOrActor(DestLocation, DestActor);
	}
}
bool AWorldController::SetNewMoveDestination_Validate(const FVector DestLocation, AActor* DestActor) { return true; }