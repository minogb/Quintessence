// Fill out your copyright notice in the Description page of Project Settings.

#include "AvatarController.h"
#include "Avatar.h"
#include "Engine/GameEngine.h"
#include "TimerManager.h"
 
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
		return 180.f;
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
	if(HasAuthority()){
		if(GoalActor){
			MoveToActor(GoalActor);
		}
		else{
			MoveToLocation(GoalLocation);
		}
	}
}

void AAvatarController::StartDoingTask(){
	IsDoingTask = true;
	if(GetWorld())
		GetWorldTimerManager().SetTimer(TaskTimer,this, &AAvatarController::TaskCompleted,GetCurrentTaskDuration(),false);
}

void AAvatarController::Stop(){
	if(HasAuthority()){
		InteruptTask();
		GoalActor = nullptr;
		GoalAction = No_Interaction;
		GoalLocation = INVALID_LOCATION;
	}
}

void AAvatarController::InteruptTask(){
	IsDoingTask= false;
	StopMovement();
	GetWorldTimerManager().ClearTimer(TaskTimer);
}

float AAvatarController::GetCurrentTaskDuration(){
	switch(GoalAction){
	case Attack:
		//Calculate based on weapon
		return 2.f;
	case Follow:
		0.5;
	default:
		return 1.f;
	}
}

float AAvatarController::GetCurrentTaskCoolDownDuration(){
	switch(GoalAction){
	case Attack:
		//Calculate based on weapon
		return 2.f;
	case Follow:
		return 0.5;
	default:
		return 1.f;
	}
}

void AAvatarController::TaskCompleted(){
	//Once we are done we are no longer working on the task
	IsDoingTask = false;
	//Every task has a cool down period to prevent future tasks
	IsTaskOnCoolDown = true;
	
	switch(GoalAction){
	case Attack:
		//Attack
		break;
	default:
		break;
	}
	if(GEngine)
      GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Task Completed")); 
	//Set how long we are on cool down for
	if(GetWorld())
		GetWorldTimerManager().SetTimer(TaskTimer,this, &AAvatarController::EndTaskCooldown,GetCurrentTaskCoolDownDuration(),false);
}

void AAvatarController::EndTaskCooldown(){
	IsTaskOnCoolDown = false;
}

bool AAvatarController::ValidTask(){
	return (GoalActor && GoalAction != No_Interaction) || !GoalLocation.Equals(INVALID_LOCATION);
}

void AAvatarController::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
	if(ValidTask()){
		//At goal
		if(IsAtGoal()){
			//Can do task
			if(!IsDoingTask && !IsTaskOnCoolDown){
				StartDoingTask();
			}
			//if can't do task, do nothing
		}
		//Am I not doing anything? and am I 
		else{
			//Am I not at goal and doing a task?
			if(IsDoingTask){
				//stop doing task out of range
				InteruptTask();
			}
			//If I am not at goal move to goal
			MoveToLocationOrGoal();
		}
	}
}