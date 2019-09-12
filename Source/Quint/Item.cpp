// Fill out your copyright notice in the Description page of Project Settings.

#include "Item.h"
#include "UnrealNetwork.h"
#include "ConstructorHelpers.h"
#include "UObject/UObjectGlobals.h"
#include "Engine/GameEngine.h"
#include "Json/Public/Serialization/JsonReader.h"
#include "Json/Public/Serialization/JsonSerializer.h"
#include "JsonUtilities/Public/JsonObjectConverter.h"

void UItem::Combine(UItem*& that){
	if(that && !this->IsA(that->GetClass()))
		return;
	int Amount = FMath::Clamp(StackSize+that->StackSize,0,MaxStackSize);
	that->StackSize -= Amount - StackSize;
	StackSize= Amount;
	if(that->StackSize<=0){
		that = nullptr;
	}
	
}

UItem::UItem() {
	ImageTexture = CreateDefaultSubobject<UTexture2D>("Image");
	Actions = TArray<EItemAction>();
	//TODO:Replace image texture to get it from the item index table
	ConstructorHelpers::FObjectFinder<UTexture2D> TextureFinder(TEXT("/Game/UserInterface/Icons/axe.axe"));
	if (TextureFinder.Succeeded()) {
		ImageTexture = TextureFinder.Object;
	}
}

FString UItem::GetSaveJSON()
{
	FString JSON;
	TSharedRef <TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&JSON);
	JsonWriter->WriteObjectStart();
	JsonWriter->WriteValue("ID", UniqueItemId);
	JsonWriter->WriteValue("StackSize", StackSize);
	JsonWriter->WriteObjectEnd();
	JsonWriter->Close();
	return JSON;
}

void UItem::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );
	DOREPLIFETIME(UItem, StackSize);
	DOREPLIFETIME(UItem, bReplicatedFlag);
	DOREPLIFETIME(UItem, Owner);
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