// Fill out your copyright notice in the Description page of Project Settings.

#include "AvatarController.h"
#include "Avatar.h"
#include "Engine/GameEngine.h"

void AAvatarController::SetLocationGoal(FVector GoalLocation){
	if(HasAuthority()){
		MoveToLocation(GoalLocation);   
	}
}

void AAvatarController::SetGoalAndAction(AActor * Goal, bool Action){
}
