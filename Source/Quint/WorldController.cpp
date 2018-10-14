// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldController.h"
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
	APawn* const MyPawn = GetPawn();
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);

	if (HitResult.bBlockingHit && MyPawn) {
		float const Distance = FVector::Dist(HitResult.ImpactPoint, MyPawn->GetActorLocation());
		//Should we bother with the network call
		if (Distance > 120)
			// We hit something, move there
			SetNewMoveDestination(HitResult.ImpactPoint, HitResult.Actor.Get());
	}
}

void AWorldController::OnSetDestinationPressed()
{
}

void AWorldController::OnSetDestinationReleased()
{
	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit) {
		float const Distance = FVector::Dist(Hit.Location, GetPawn()->GetActorLocation());
		// We hit something, move there
		if (Hit.Actor.Get() || Distance > 120)
			SetNewMoveDestination(Hit.ImpactPoint, Hit.Actor.Get());
	}
}


void AWorldController::SetNewMoveDestination_Implementation(const FVector DestLocation, AActor* DestActor){

}
bool AWorldController::SetNewMoveDestination_Validate(const FVector DestLocation, AActor* DestActor) { return true; }