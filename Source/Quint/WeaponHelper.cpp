// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponHelper.h"
#include "Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "QuintDamageType.h"
UWeaponHelper::UWeaponHelper() :Super(){
	if (!WeaponLookupTable) {
		static ConstructorHelpers::FObjectFinder<UDataTable> WeaponTable(TEXT("DataTable'/Game/DataTables/WeaponDataTable.WeaponDataTable'"));
		if (WeaponTable.Succeeded())
			WeaponLookupTable = WeaponTable.Object;
	}
}
bool UWeaponHelper::GetWeaponStructFromId(int id, FWeaponDataStruct & weaponStruct){
	if(!WeaponLookupTable)
		return false;
	FWeaponDataStruct* data = nullptr;
	if(WeaponLookupTable)
		data = WeaponLookupTable->FindRow<FWeaponDataStruct>(FName(*FString::FromInt(id)), WEAPON_CONTEXT_STRING, false);
	weaponStruct = data ? *data : FWeaponDataStruct();
	return data != nullptr;

}

bool UWeaponHelper::GetWeaponOrDefault(int id, FWeaponDataStruct & weaponStruct){
	if(GetWeaponStructFromId(id, weaponStruct))
		return true;
	return GetWeaponStructFromId(0, weaponStruct);
}

int UWeaponHelper::GetWeaponDamageForPlayById(int id, int playerId){
	if(!WeaponLookupTable)
		return false;
	FWeaponDataStruct weaponData;
	//todo: Fplayer level data struct
	int playerlvl = 1;
	if(GetWeaponStructFromId(id, weaponData)){
		//todo: use player level to adjust base damage
		int damageBase = weaponData.BaseDamage;
		float totalScale = 0;
		//todo: need player scale level
		totalScale+=GetPercentFromScale(weaponData.AgilityScale,100);
		totalScale+=GetPercentFromScale(weaponData.StregnthScale,100);
		totalScale+=GetPercentFromScale(weaponData.DexterityScale,100);
		return FMath::FRandRange(damageBase, damageBase + (damageBase*totalScale));
	}
	return 0;
}

float UWeaponHelper::GetPercentFromScale(TEnumAsByte<EWeaponScaleEnum> scale, int playerScaleLevel){
	switch(scale.GetValue()){
	case S_Scale:
		return 1.25 * (playerScaleLevel/100);
		break;
	case A_Scale:
		return 1.f * (playerScaleLevel/100);
		break;
	case B_Scale:
		return 0.75 * (playerScaleLevel/100);
		break;
	case C_Scale:
		return 0.5 * (playerScaleLevel/100);
		break;
	case D_Scale:
		return 0.25 * (playerScaleLevel/100);
		break;
	default:
		return 0.f;
		break;
	}
	return 0.0f;
}

TSubclassOf<UQuintDamageType> UWeaponHelper::GetWeaponDamageType(int id)
{
	return UQuintDamageType::StaticClass();
}
