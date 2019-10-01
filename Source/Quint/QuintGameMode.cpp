#include "QuintGameMode.h"
#include "PlayerVessel.h"
#include "QuintPlayerController.h"
#include "Engine/World.h"
#include "Avatar.h"
#include "PlayerVessel.h"
#include "Engine/GameEngine.h"
#include "QuintPlayerController.h"
#include "ConstructorHelpers.h"
#include "Json/Public/Dom/JsonObject.h"
#include "Json/Public/Serialization/JsonReader.h"
#include "Json/Public/Serialization/JsonSerializer.h"
#include "JsonUtilities/Public/JsonObjectConverter.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/GameSession.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

AQuintGameMode::AQuintGameMode(){

	DefaultPawnClass = APlayerVessel::StaticClass();
	PlayerControllerClass  = AQuintPlayerController::StaticClass();
	Http = &FHttpModule::Get();
	SaveTask = new FAutoDeleteAsyncTask<FSaveTask>(this);
	SaveTask->StartBackgroundTask();
	
}

void AQuintGameMode::CallToGetPlayerInfo(int PlayerID){

	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &AQuintGameMode::OnPlayerInfoReceived);
	//This is the url on which to process the request
	Request->SetURL("localhost");
	Request->SetVerb("POST");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));

	//Start making content request data
	FString jsonString;
	TSharedRef <TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&jsonString);
	//Write json data
	JsonWriter->WriteObjectStart();
	JsonWriter->WriteValue("request", TEXT("load"));
	JsonWriter->WriteValue("ID", FString::FromInt(PlayerID));

	//End content creation
	JsonWriter->WriteObjectEnd();
	JsonWriter->Close();

	//Set html content
	Request->SetContentAsString(jsonString);
	Request->ProcessRequest();
}

void AQuintGameMode::OnPlayerInfoReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful){
	if (!bWasSuccessful) {
		return;
	}
	//Create a pointer to hold the json serialized data
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());

	//Create a reader pointer to read the json data
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

	//Deserialize the json data given Reader and the actual object to deserialize
	if (FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		int32 playerId = 0;
		if(JsonObject->HasField("ID"))
			playerId = JsonObject->GetIntegerField("ID");

		if (JsonObject->HasField("ID") && JsonObject->HasField("X") && JsonObject->HasField("Y") && JsonObject->HasField("Z")
			&& JsonObject->HasField("Inventory") && JsonObject->HasField("Equipment") && JsonObject->HasField("Skills")) {
			//If the current player is logged into our system
			if (UnLoggedPlayers.Contains(playerId) && !Players.Contains(playerId)) {
				//Add player to the logged list
				Players.Add(playerId, UnLoggedPlayers[playerId].Player);
				//Remove player from the unloged list
				UnLoggedPlayers.Remove(playerId);
				//Get player data
				float x = (float)JsonObject->GetNumberField("X");
				float y = (float)JsonObject->GetNumberField("Y");
				float z = (float)JsonObject->GetNumberField("Z");
				float health = (float)JsonObject->GetNumberField("Health");
				//Create player avatar
				SpawnPlayerAvatar(playerId, x, y, z, health);

				FString name = JsonObject->GetStringField("Name");
				//Set player name
				Players[playerId]->PlayerState->SetPlayerName(name);
				//Setup player data like inventory
				Players[playerId]->InitWithJSON(JsonObject->GetObjectField("Inventory"),
					JsonObject->GetObjectField("Equipment"), JsonObject->GetObjectField("Skills"));
			}
			else if(Players.Contains(playerId)){
				//player already logged in

			}
		}
		//No valid player found / invalid player info retrieved
		else if(JsonObject->HasField("ID") && UnLoggedPlayers.Contains(playerId)) {
			//TOD: GameSession->KickPlayer(UnLoggedPlayers[playerId].Player, FText::FromString("Internal Server Error"));
		}
	}
}

void AQuintGameMode::SpawnPlayerAvatar(int PlayerID, float X, float Y, float Z, float Health){
	if (Players.Contains(PlayerID)) {
		if (GetWorld()) {
			FActorSpawnParameters spawnInfo = FActorSpawnParameters();
			spawnInfo.Owner = Players[PlayerID];
			FVector location = FVector(X,Y,Z);
			AAvatar * avatar = nullptr;
			if (IsValid(PlayerAvatarClass)) {
				avatar = GetWorld()->SpawnActor<AAvatar>(PlayerAvatarClass, location, FRotator(0), spawnInfo);
			}
			else {
				avatar = GetWorld()->SpawnActor<AAvatar>(location, FRotator(0), spawnInfo);
			}
			APlayerVessel* vessel = Cast<APlayerVessel>(Players[PlayerID]->GetPawn());
			if (vessel) {
				//Set the state of player avatar from our pawn
				avatar->SetPlayerState(vessel->GetPlayerState());
				avatar->SetHealth(Health);
				//Set the avatar for reference in the pawn
				vessel->SetPlayerAvater(avatar, Players[PlayerID]);
				AQuintPlayerController* player = Cast<AQuintPlayerController>(Players[PlayerID]);
				if (player) {
					player->SetPlayerAvatar(avatar);
				}
			}
		}
	}
}

void AQuintGameMode::PreformBackgroundTasks()
{
	SaveTask = new FAutoDeleteAsyncTask<FSaveTask>(this);
	SaveTask->StartBackgroundTask();
}

void AQuintGameMode::PostLogin(APlayerController * NewPlayer){
	Super::PostLogin(NewPlayer);
	//todo: remove
	NewPlayer->PlayerState->PlayerId = 1;

	FPlayerLogStruct log = FPlayerLogStruct();
	log.Player = Cast<AQuintPlayerController>(NewPlayer);
	log.TimeStamp = UGameplayStatics::GetRealTimeSeconds(GetWorld());
	UnLoggedPlayers.Add(NewPlayer->PlayerState->PlayerId, log);

	if (!PreformBackgroundTasksTimer.IsValid() && GetWorld())
		GetWorldTimerManager().SetTimer(PreformBackgroundTasksTimer, this, &AQuintGameMode::PreformBackgroundTasks, TimeBetweenBackgroundTasks, true);
	CallToGetPlayerInfo(NewPlayer->PlayerState->PlayerId);
}

void FSaveTask::DoWork(){
	GM->RemoveAfkPlayers();
	GM->SavePlayers();
	GM->RemoveUnloggedPlayers();
	
	this->Abandon();
}

FSaveTask::FSaveTask(AQuintGameMode* GameMode)
{
	GM = GameMode;
}

void AQuintGameMode::RemoveAfkPlayers(){
	//TODO:
}
void AQuintGameMode::RemoveUnloggedPlayers()
{
	int now = UGameplayStatics::GetRealTimeSeconds(GetWorld());
	for (TPair<int, FPlayerLogStruct> current : UnLoggedPlayers) {
		if (current.Value.TimeStamp * 60 * 2 <= now) {
			//GameSession->KickPlayer(current.Value.Player, FText::FromString("Could not load player data in time"));

		}
	}
}
void AQuintGameMode::SavePlayers() {
	TSharedPtr<FJsonObject> List;
	FString jsonString = "";
	TSharedRef <TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&jsonString);
	JsonWriter->WriteObjectStart();
	JsonWriter->WriteValue("request", TEXT("save"));
	bool makeSave = false;
	JsonWriter->WriteArrayStart("Players");
	for (TPair<int, AQuintPlayerController*> current : Players) {
		if (IsValid(current.Value)) {
			JsonWriter->WriteRawJSONValue(current.Value->GetSaveJSON());
			makeSave = true;
		}
	}
	JsonWriter->WriteArrayEnd();

	JsonWriter->WriteObjectEnd();
	JsonWriter->Close();
	if (makeSave) {
		TSharedRef<IHttpRequest> Request = Http->CreateRequest();
		//This is the url on which to process the request
		Request->SetURL("localhost");
		Request->SetVerb("POST");
		Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
		Request->SetHeader("Content-Type", TEXT("application/json"));
		Request->SetContentAsString(jsonString);
		Request->ProcessRequest();
	}

}