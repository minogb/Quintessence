// Fill out your copyright notice in the Description page of Project Settings.

#include "Item.h"
#include "UnrealNetwork.h"


void UItem::Combine(UItem*& that){
	if(that->GetID() != this->GetID())
		return;
	int Amount = FMath::Clamp(StackSize+that->StackSize,0,MaxStackSize);
	that->StackSize -= Amount - StackSize;
	StackSize= Amount;
	if(that->StackSize<=0){
		that = nullptr;
	}
	
}



void UItem::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );
	DOREPLIFETIME(UItem, StackSize);
	DOREPLIFETIME(UItem, bReplicatedFlag);
}
UItem * UItem::CREATE_ITEM(AActor* Outer, TSubclassOf<UItem> SubClass, int Amount)
{
	//ConstructObject
	UItem* newObj = NewObject<UItem>(Outer,SubClass);
	if(IsValid(newObj)){
		newObj->SetStackSize(Amount);
	}
	return newObj;
}