// Fill out your copyright notice in the Description page of Project Settings.

#include "Interactable.h"
#include "Item.h"
#include "Avatar.h"


float IInteractable::GetSize_Implementation(){
	return 32.f;
}
bool IInteractable::IsValidTask_Implementation(TEnumAsByte<EInteractionType> Task, AAvatar* Player) {
	return (GetAvaliableTasks_Implementation() & (uint8)Task.GetValue()) == (uint8)Task.GetValue();
}