// Fill out your copyright notice in the Description page of Project Settings.

#include "Item.h"
#include "UnrealNetwork.h"
#include "ConstructorHelpers.h"
#include "UObject/UObjectGlobals.h"
#include "Engine/GameEngine.h"
#include "Json/Public/Serialization/JsonReader.h"
#include "Json/Public/Serialization/JsonSerializer.h"
#include "JsonUtilities/Public/JsonObjectConverter.h"
#include "UObject/UObjectGlobals.h"

#define PrintToScreen(x) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, FString(x));}

UDataTable* UItem::DataTable = nullptr;
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


void UItem::InitItemID(){

	if (WaitingOrHasID || ItemTableID == 0)
		return;
	WaitingOrHasID = true;
	//Start making content request data
	FString jsonString;
	TSharedRef <TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&jsonString);
	//Create Item ID
	JsonWriter->WriteObjectStart();
		
	JsonWriter->WriteValue("request", TEXT("createItemID"));
	JsonWriter->WriteValue("ItemTableID", FString::FromInt(ItemTableID));
	//End content creation
	JsonWriter->WriteObjectEnd();
	JsonWriter->Close();
	FHttpModule* Http;
	Http = &FHttpModule::Get();
	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UItem::OnItemDataRecived);
	//This is the url on which to process the request
	Request->SetURL("localhost");
	Request->SetVerb("POST");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));

	Request->SetContentAsString(jsonString);
	Request->ProcessRequest();

}

void UItem::OnItemDataRecived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful){
	PrintToScreen(Response->GetContentAsString());
	//Create a pointer to hold the json serialized data
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());

	//Create a reader pointer to read the json data
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	//Deserialize the json data given Reader and the actual object to deserialize
	if (FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		if (JsonObject->HasField("ID"))
			UniqueItemId = JsonObject->GetIntegerField("ID");
	}
}

UItem::UItem() {
	Actions = TArray<EItemAction>();
}

void UItem::InitWithJson(TSharedPtr<FJsonObject> JsonData){
	if (JsonData) {
		if (JsonData->HasField("ID")) {
			UniqueItemId = JsonData->GetIntegerField("ID");
		}
		if (JsonData->HasField("StackCount")) {
			SetStackSize(JsonData->GetIntegerField("StackCount"));
		}
	}
}

FString UItem::GetSaveJSON()
{
	FString JSON;
	TSharedRef <TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&JSON);
	JsonWriter->WriteObjectStart();
	JsonWriter->WriteValue("UniqueID", UniqueItemId);
	JsonWriter->WriteValue("TableID", ItemTableID);
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

UItem * UItem::CreateItemFromTable(int TableID, AActor* Owner, TSharedPtr<FJsonObject> JsonData) {
	FItemIndex itemData;
	if (UItem::GetItemIndex(TableID, itemData)) {
		PrintToScreen(itemData.ItemName);
		UItem* item = NewObject<UItem>(Owner,itemData.ItemClass);
		item->InitWithJson(JsonData);
		return item;
	}
	return nullptr;
}

bool UItem::GetItemIndex(int TableID, FItemIndex& Result) {
	if (!UItem::DataTable) {
		DataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Items/ItemIndexTable.ItemIndexTable"));
	}
	if (UItem::DataTable) {
		FString contextString;
		FName Name;
		FItemIndex* result = UItem::DataTable->FindRow<FItemIndex>(FName(*FString::FromInt(TableID)), contextString);
		if (result) {
			Result = *result;
			return true;
		}
	}
	return false;
}

bool UItem::GetItemIndexFromSubclass(TSubclassOf<UItem> ItemClass, FItemIndex& Result) {
	UItem* defaultVal = Cast<UItem>(ItemClass->GetDefaultObject());
	if (defaultVal) {
		return UItem::GetItemIndex(defaultVal->ItemTableID, Result);
	}
	return false;
}