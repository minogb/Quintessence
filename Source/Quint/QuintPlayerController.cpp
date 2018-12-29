// Fill out your copyright notice in the Description page of Project Settings.

#include "QuintPlayerController.h"
#include "Engine/World.h"
#include "Avatar.h"
#include "PlayerVessel.h"
#include "Engine/GameEngine.h"
#include "AvatarController.h"
AQuintPlayerController::AQuintPlayerController(){
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

}

bool AQuintPlayerController::SetPlayerAvatar(AAvatar * avatar){
	if(HasAuthority()){
		PlayerAvatar = avatar;
		return PlayerAvatar != nullptr;
	}
	return false;
}

void AQuintPlayerController::BeginPlay(){
}

void AQuintPlayerController::SetDestinationOrGoal(){
	FHitResult Hit;
	bool GotGoal = false;
	if(GetHitResultUnderCursor(ECC_Interactable, false, Hit)){
		AActor* hitActor = Hit.GetActor();
		if(hitActor && hitActor != PlayerAvatar){
			//TODO: Get default Action
			GotGoal = true;
			if(GEngine){
			  GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *FString(PlayerAvatar== nullptr? "valid":"invalid"));   
			}
		}
		else{
			GotGoal = false;
		}
	}
	if (!GotGoal && GetHitResultUnderCursor(ECC_Floor, false, Hit)){
		float const Distance = FVector::Dist(Hit.Location, GetPawn()->GetActorLocation());
		Server_SetDestination(Hit.ImpactPoint);
	}
}

bool AQuintPlayerController::IsValidLocation(FVector location){
	return !location.Equals(FVector(0),1);
}

void AQuintPlayerController::Server_SetDestination_Implementation  (FVector Location){
	if(PlayerAvatar && HasAuthority() && IsValidLocation(Location)){
		Cast<AAvatarController>(PlayerAvatar->GetController())->SetLocationGoal(Location);
	}
	if(GEngine){
      //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));   
	}
}
void AQuintPlayerController::Server_SetGoalAndAction_Implementation  (AActor * Goal, bool Action){
	
	if(PlayerAvatar && HasAuthority() && Goal){
		Cast<AAvatarController>(PlayerAvatar->GetController())->SetGoalAndAction(Goal, Action);
	}
}

bool AQuintPlayerController::Server_SetDestination_Validate (FVector Location){
	return true;
}
bool AQuintPlayerController::Server_SetGoalAndAction_Validate (AActor * Goal, bool Action){
	return true;
}

void AQuintPlayerController::SetupInputComponent(){
	// set up gameplay key bindings
	Super::SetupInputComponent();
	InputComponent->BindAction("SetDestination", IE_Released, this, 
		&AQuintPlayerController::SetDestinationOrGoal);
}