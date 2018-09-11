// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "QuintDamageType.generated.h"

/**
 * 
 */

UCLASS()
class QUINT_API UQuintDamageType : public UDamageType
{
	GENERATED_BODY()
	/*
	pure damage - no damage can block this

	Non-magic
		DULL - Only base armor can block this
		Blunt
		Cleave
		Peircing
	Magic
		DULL - Only base magic resistance can block this
		Cold
		Heat
		Electric
	Effect
		Bleed
		Shock             
	*/	
};