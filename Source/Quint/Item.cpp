// Fill out your copyright notice in the Description page of Project Settings.

#include "Item.h"
#include "UnrealNetwork.h"

void UItem::Combine(UItem*& that){
	if(that->GetID() != this->GetID())
		return;
	int Amount = FMath::Clamp(StackSize+that->StackSize,0,MaxStackSize);
	that->StackSize -= Amount - StackSize;
	if(that->StackSize<=0){
		that = nullptr;
	}
	
}

void UItem::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const{
	DOREPLIFETIME(UItem, StackSize);
}