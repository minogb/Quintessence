// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CraftingInfo.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "QuintGameMode.generated.h"

/**
 * 
 */

class AQuintPlayerController;
class FSaveTask : public FNonAbandonableTask {
	friend class FAutoDeleteAsyncTask<FSaveTask>;
protected:
	FTimerHandle SavePlayerTimer;
	void DoWork();
	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(FMyTaskName, STATGROUP_ThreadPoolAsyncTasks);
	}
	AQuintGameMode* GM;
public:
	FSaveTask(AQuintGameMode* GameMode);
};
USTRUCT(BlueprintType)
struct FPlayerLogStruct {
	GENERATED_BODY()
	AQuintPlayerController* Player;
	int TimeStamp;
};
UCLASS()
class QUINT_API AQuintGameMode : public AGameModeBase
{
	friend class FSaveTask;
	GENERATED_BODY()

	FAutoDeleteAsyncTask<FSaveTask>* SaveTask;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AAvatar> PlayerAvatarClass;

	TMap<int, FPlayerLogStruct> UnLoggedPlayers;
	TMap<int, AQuintPlayerController*> Players;

	FHttpModule* Http;

	FTimerHandle PreformBackgroundTasksTimer;
	float TimeBetweenBackgroundTasks = 1.f;

	//Make http request to get player info to spawn
	void CallToGetPlayerInfo(int PlayerID); 
	//Call back from http get player request / used to spawn
	void OnPlayerInfoReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	//TODO: Remove
	void OnSaveResultReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void SpawnPlayerAvatar(int PlayerID, float X, float Y, float Z, float Health);

	void PreformBackgroundTasks();

	//Remove players whoms connection timed out
	void RemoveUnloggedPlayers();
	//Remove afk/disconneccted players
	void RemoveAfkPlayers();
	//Save all valid players
	void SavePlayers();
public:
	AQuintGameMode();

protected:
	virtual void PostLogin(APlayerController* NewPlayer) override;
};
