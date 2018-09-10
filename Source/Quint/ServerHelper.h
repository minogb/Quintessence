// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class QUINT_API ServerHelper
{
private:
	ServerHelper();
	~ServerHelper();
public:
	static void SavePlayerPositionToServer(class AQuintCharacter* player){}
	static int CreatePlayer() { return 0; }
};
