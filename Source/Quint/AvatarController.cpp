// Fill out your copyright notice in the Description page of Project Settings.

#include "AvatarController.h"
#include "Avatar.h"
#include "Engine/GameEngine.h"
 
void AAvatarController::SetLocationGoal(FVector Location){
	if(HasAuthority()){
		Stop();
		GoalLocation = Location;
	}
}

void AAvatarController::SetGoalAndAction(AActor * Goal, EInteractionType Action){ 
	if(HasAuthority()){
		Stop();
		GoalActor = Goal;
		GoalAction = Action;
	}
}

float AAvatarController::GetGoalDistance(){
	switch(GoalAction){
	case Attack:
		//Calculate based on weapon
		return 0.f;
	default:
		return 10.f;
	}
}

bool AAvatarController::IsAtGoal(){
	if(GoalActor){
		return GetPawn()->GetActorLocation().Equals(GoalActor->GetActorLocation(),GetGoalDistance());
	}
	else{
		//If invalid location we are always at goal, otherwise use calculated distance
		return GoalLocation.Equals(INVALID_LOCATION) || GetPawn()->GetActorLocation().Equals(GoalLocation,GetGoalDistance());
	}
}

void AAvatarController::MoveToLocationOrGoal(){
	if(HasAuthority() && !IsAtGoal()){
		if(GoalActor){
			MoveToActor(GoalActor);
		}
		else{
			MoveToLocation(GoalLocation);
		}
	}
}

void AAvatarController::Stop(){
	if(HasAuthority()){
		GoalActor = nullptr;
		GoalAction = No_Interaction;
		GoalLocation = INVALID_LOCATION;
	}
	StopMovement();
}

void AAvatarController::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
	if(!IsDoingTask)
		MoveToLocationOrGoal();
}