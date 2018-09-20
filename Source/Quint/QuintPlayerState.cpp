// Fill out your copyright notice in the Description page of Project Settings.

#include "QuintPlayerState.h"
#include "UnrealNetwork.h"
#include "Engine.h"



void AQuintPlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AQuintPlayerState, Attackable);

	DOREPLIFETIME(AQuintPlayerState, Helm);
	DOREPLIFETIME(AQuintPlayerState, Chest);
	DOREPLIFETIME(AQuintPlayerState, Greaves);
	DOREPLIFETIME(AQuintPlayerState, Gloves);
	DOREPLIFETIME(AQuintPlayerState, PrimaryWeapon);
	DOREPLIFETIME(AQuintPlayerState, SecondaryWeapon);
}
AQuintPlayerState::AQuintPlayerState(){

}

void AQuintPlayerState::OnRepHelm(){
}

void AQuintPlayerState::OnRepChest(){
}

void AQuintPlayerState::OnRepGreaves(){
}

void AQuintPlayerState::OnRepGloves(){
}

void AQuintPlayerState::OnRepPrimaryWeapon(){
}

void AQuintPlayerState::OnRepSecondaryWeapon(){
}

void AQuintPlayerState::OnRepAttackable(){
}


//TODO: verify/save to server
bool AQuintPlayerState::SetPlayerHelm(int32 helm){
	if(!HasAuthority())
		return false;
	Helm = helm;
	OnRepHelm();
	return false;
}

bool AQuintPlayerState::SetPlayerChest(int32 chest){
	if(!HasAuthority())
		return false;
	Chest = chest;
	OnRepChest();
	return false;
}

bool AQuintPlayerState::SetPlayerGreaves(int32 greaves){
	if(!HasAuthority())
		return false;
	Greaves = greaves;
	OnRepGreaves();
	return false;
}
bool AQuintPlayerState::SetPlayerGloves(int32 gloves){
	if(!HasAuthority())
		return false;
	Gloves = gloves;
	OnRepGloves();
	return false;
}

bool AQuintPlayerState::SetPlayerPrimary(int32 primaryWeapon){
	if(!HasAuthority())
		return false;
	PrimaryWeapon = primaryWeapon;
	OnRepPrimaryWeapon();
	return false;
}

bool AQuintPlayerState::SetPlayerSecondaryWeapon(int32 secondaryWeapon){
	if(!HasAuthority())
		return false;
	SecondaryWeapon = secondaryWeapon;
	OnRepSecondaryWeapon();
	return false;
}

