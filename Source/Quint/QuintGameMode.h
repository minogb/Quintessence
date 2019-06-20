// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Enumerations.h"
#include "QuintGameMode.generated.h"

/**
 * 
 */
UCLASS()
class QUINT_API AQuintGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	AQuintGameMode();
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AAvatar> PlayerAvatarClass;
	class UDataTable* RecipeTable;
	bool GetOutputofRecipe(FName Row, FCraftingStruct& Output);
protected:
	virtual void PostLogin(APlayerController* NewPlayer) override;
};
