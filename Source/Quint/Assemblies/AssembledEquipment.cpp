// Fill out your copyright notice in the Description page of Project Settings.


#include "AssembledEquipment.h"
#include "Avatar.h"
#include "Interfaces/ComponentInterface.h"

bool UAssembledEquipment::SetComponents(TArray<UItem*>& Components){
	for (UItem* current : Components) {
		if(!SetComponent(current))
			return false;
	}
	return true;
}

bool UAssembledEquipment::OnIncomingDamage_Implementation(UPARAM(ref)FDamageStruct & Damage, UObject * DamageCauser, AController * CauserController){
	for (UObject*current : GetComponents()) {
		if (IsValid(current) && current->GetClass()->ImplementsInterface(UEffectInterface::StaticClass())) {
			IEffectInterface::Execute_OnIncomingDamage(current, Damage, DamageCauser, CauserController);
		}
	}
	return false;
}

bool UAssembledEquipment::OnDamageTaken_Implementation(UPARAM(ref)FDamageStruct & Damage, UObject * DamageCauser, AController * CauserController){
	for (UObject*current : GetComponents()) {
		if (IsValid(current) && current->GetClass()->ImplementsInterface(UEffectInterface::StaticClass())) {
			IEffectInterface::Execute_OnDamageTaken(current, Damage, DamageCauser, CauserController);
		}
	}
	return false;
}

bool UAssembledEquipment::OnOutgoingDamage_Implementation(UPARAM(ref)FDamageStruct & Damage, UObject * DamageTarget){
	for (UObject*current : GetComponents()) {
		if (IsValid(current) && current->GetClass()->ImplementsInterface(UEffectInterface::StaticClass())) {
			IEffectInterface::Execute_OnOutgoingDamage(current, Damage, DamageTarget);
		}
	}
	return false;
}

bool UAssembledEquipment::OnDamageDelt_Implementation(FDamageStruct & Damage, UObject * DamageTarget){
	for (UObject*current : GetComponents()) {
		if (IsValid(current) && current->GetClass()->ImplementsInterface(UEffectInterface::StaticClass())) {
			IEffectInterface::Execute_OnDamageDelt(current, Damage, DamageTarget);
		}
	}
	return false;
}

bool UAssembledEquipment::OnActionSpeedCalculation_Implementation(UPARAM(ref) float & Speed, EInteractionType Action){
	for (UObject*current : GetComponents()) {
		if (IsValid(current) && current->GetClass()->ImplementsInterface(UEffectInterface::StaticClass())) {
			IEffectInterface::Execute_OnActionSpeedCalculation(current, Speed, Action);
		}
	}
	return false;
}

bool UAssembledEquipment::OnActionCoolDownCalculation_Implementation(UPARAM(ref) float & Duration, EInteractionType Action){
	for (UObject*current : GetComponents()) {
		if (IsValid(current) && current->GetClass()->ImplementsInterface(UEffectInterface::StaticClass())) {
			IEffectInterface::Execute_OnActionCoolDownCalculation(current, Duration, Action);
		}
	}
	return false;
}

int UAssembledEquipment::OnCalculateSkillLevel_Implementation(ESkillType Skill, int Level){
	int retVal = 0;
	for (UObject*current : GetComponents()) {
		if (IsValid(current) && current->GetClass()->ImplementsInterface(UEffectInterface::StaticClass())) {
			int currentLevel = IEffectInterface::Execute_OnCalculateSkillLevel(current, Skill, Level);
			if (currentLevel > retVal)
				retVal = currentLevel;
		}
	}
	return retVal;
}

TArray<FSkillLevelStruct> UAssembledEquipment::GetSkillsRequired_Implementation(){

	TArray<FSkillLevelStruct> retVal = TArray<FSkillLevelStruct>();

	for (UObject*current : GetComponents()) {
		if (IsValid(current) && current->GetClass()->ImplementsInterface(UComponentInterface::StaticClass())) {
			retVal.Append(IComponentInterface::Execute_GetUseSkillRequired(current));
		}
	}
	return retVal;
}

bool UAssembledEquipment::CanPlayerEquip_Implementation(AAvatar* Player){

	if (IsValid(Player)) {
		for (FSkillLevelStruct current : GetSkillsRequired()) {
			//The first time we can't equip, return false
			if (Player->GetSkillLevel(current.Skill) < current.Level)
				return false;
		}
		//return true
		return true;
	}
	//Player can't equip if he dosn't exist
	return false;
}
