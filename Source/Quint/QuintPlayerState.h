// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "QuintPlayerState.generated.h"

/**
 * 
 */
USTRUCT(Blueprintable)
struct QUINT_API FEquipmentStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	int32 Helm;
	UPROPERTY(BlueprintReadOnly)
	int32 Chest;
	UPROPERTY(BlueprintReadOnly)
	int32 Greaves;
	UPROPERTY(BlueprintReadOnly)
	int32 Boots;
	UPROPERTY(BlueprintReadOnly)
	int32 Gloves;
	UPROPERTY(BlueprintReadOnly)
	int32 PrimaryWeapon;
	UPROPERTY(BlueprintReadOnly)
	int32 SecondaryWeapon;
};
UENUM(BlueprintType)
enum EProtectionState {
	//Can be attacked without consiquince
	Assailable UMETA(DisplayName = "Assailable"),
	//cannot be attacked
	Protected UMETA(DisplayName = "Protected"),
	//can be attacked with consiquince
	Neutral UMETA(DisplayName = "Neutral")
};
UCLASS(Blueprintable)
class QUINT_API AQuintPlayerState : public APlayerState
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRepHelm)
	int32 Helm;
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRepChest)
	int32 Chest;
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRepGreaves)
	int32 Greaves;
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRepEquipment)
	int32 Gloves;
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRepPrimaryWeapon)
	int32 PrimaryWeapon;
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRepSecondaryWeapon)
	int32 SecondaryWeapon;

	UPROPERTY(ReplicatedUsing = OnRepAttackable)
	TEnumAsByte<EProtectionState> Attackable = Neutral;
public:
protected:
	UFUNCTION()
	void OnRepEquipment() {};
	UFUNCTION()
	void OnRepHelm();

	UFUNCTION()
	void OnRepChest();

	UFUNCTION()
	void OnRepGreaves();
	
	UFUNCTION()
	void OnRepGloves();

	UFUNCTION()
	void OnRepPrimaryWeapon();

	UFUNCTION()
	void OnRepSecondaryWeapon();

	UFUNCTION()
	void OnRepAttackable() {}
public:
	AQuintPlayerState();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetPlayerHelm(){return Helm;}
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetPlayerChest(){return Chest;}
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetPlayerGreaves(){return Greaves;}
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetPlayerGloves(){return Gloves;}
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetPlayerPrimaryWeapon(){return PrimaryWeapon;}
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetPlayerSecondaryWeapon(){return SecondaryWeapon;}
	UFUNCTION(BlueprintCallable, BlueprintPure)
	EProtectionState GetAttackableState() { return Attackable.GetValue(); }

	//TODO: Add verification check on player stats and equipment type
	bool SetPlayerEquipment(FEquipmentStruct equipment) {return false;}
	bool SetPlayerHelm(int32 helm);
	bool SetPlayerChest(int32 chest);
	bool SetPlayerGreaves(int32 greaves);
	bool SetPlayerGloves(int32 gloves);
	bool SetPlayerPrimary(int32 primaryWeapon);
	bool SetPlayerSecondaryWeapon(int32 secondaryWeapon);

	void SetAttackable(EProtectionState attackable) { if (HasAuthority()) { Attackable = attackable; OnRepAttackable(); } }

};
