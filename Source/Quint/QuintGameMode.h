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
	FTimerHandle RemoveUnloggedPlayersTimer;
	void CallToGetPlayerInfo(int PlayerID);
	/*Assign this function to call when the GET request processes sucessfully*/
	void OnPlayerInfoReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void SpawnPlayerAvatar(int PlayerID, float X, float Y, float Z);
	void RemoveUnloggedPlayers();
public:
	AQuintGameMode();

protected:
	virtual void PostLogin(APlayerController* NewPlayer) override;
};
