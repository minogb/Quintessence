// Fill out your copyright notice in the Description page of Project Settings.

#include "QuintPlayerState.h"
#include "UnrealNetwork.h"




void AQuintPlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AQuintPlayerState, Attackable);

	DOREPLIFETIME(AQuintPlayerState, Helm);
	DOREPLIFETIME(AQuintPlayerState, Chest);
	DOREPLIFETIME(AQuintPlayerState, Greaves);
	DOREPLIFETIME(AQuintPlayerState, Boots);
	DOREPLIFETIME(AQuintPlayerState, Gloves);
	DOREPLIFETIME(AQuintPlayerState, PrimaryWeapon);
	DOREPLIFETIME(AQuintPlayerState, SecondaryWeapon);
}

void AQuintPlayerState::OnRepHelm(){
}

void AQuintPlayerState::OnRepChest(){
}

void AQuintPlayerState::OnRepGreaves(){
}

void AQuintPlayerState::OnRepBoots(){
}

void AQuintPlayerState::OnRepGloves(){
}

void AQuintPlayerState::OnRepPrimaryWeapon(){
}

void AQuintPlayerState::OnRepSecondaryWeapon(){
}


bool AQuintPlayerState::SetPlayerHelm(int32 helm){
	if(!HasAuthority())
		return false;
	OnRepHelm();
	return false;
}

bool AQuintPlayerState::SetPlayerChest(int32 chest){
	if(!HasAuthority())
		return false;
	OnRepChest();
	return false;
}

bool AQuintPlayerState::SetPlayerGreaves(int32 Greaves){
	if(!HasAuthority())
		return false;
	OnRepGreaves();
	return false;
}

bool AQuintPlayerState::SetPlayerBoots(int32 boots){
	if(!HasAuthority())
		return false;
	OnRepBoots();
	return false;
}

bool AQuintPlayerState::SetPlayerGloves(int32 gloves){
	if(!HasAuthority())
		return false;
	OnRepGloves();
	return false;
}

bool AQuintPlayerState::SetPlayerPrimary(int32 primaryWeapon){
	if(!HasAuthority())
		return false;
	OnRepPrimaryWeapon();
	return false;
}

bool AQuintPlayerState::SetPlayerSecondaryWeapon(int32 secondaryWeapon){
	if(!HasAuthority())
		return false;
	OnRepSecondaryWeapon();
	return false;
}
