// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "ComponentStructure.h"
#include "Enumerations.h"
#include "Enumerations.h"
#include "AssemblyComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class QUINT_API UAssemblyComponent : public UItem {
	GENERATED_BODY()
protected:
	//TODO: Add Material Reference some how
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setup", meta = (AllowPrivateAccess = "true"))
	EAssemblyComponentType ComponentType;
	//The set Level Required to craft with this
	//Using set levels so it does add X level per component
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setup", meta = (AllowPrivateAccess = "true"))
	TMap<ESkillType, int> CraftLevel;
	//The set level to use an item with this
	//Using set levels so it does add X level per component
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setup", meta = (AllowPrivateAccess = "true"))
	TMap<ESkillType, int> UseLevel;
	//The amount to modify the required craft level by
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setup", meta = (AllowPrivateAccess = "true"))
	TMap<ESkillType, int> CraftLevelModifier;
	//The amount to modify the required use level by
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setup", meta = (AllowPrivateAccess = "true"))
	TMap<ESkillType, int> UseLevelModifier;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Info", meta = (AllowPrivateAccess = "true"))
	TMap<EHarvestType, int> HarvestLevels;
	//How this component affects the color of the equipment
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setup", meta = (AllowPrivateAccess = "true"))
	FColor ColorModifier;
	int GetMapOfSkill(TMap<ESkillType, int> Map, ESkillType SkillType);
public:
	//When this item is used on something, like attack or mine
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnUse(UObject* on);
	virtual void OnUse_Implementation(UObject* on);
	//When this item is constructed - may remove
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnConstruct(UObject* Equipment);
	virtual void OnConstruct_Implementation(UObject* Equipment);
	//When this component recives damage _Implementation
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnDamageComponent(int& Amount);
	virtual void OnDamageComponent_Implementation(int& Amount);
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetCraftLevelOf(ESkillType Skill) { return GetMapOfSkill(CraftLevel, Skill); };
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetUseLevel(ESkillType Skill) { return GetMapOfSkill(UseLevel, Skill); };
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetCraftLevelModifier(ESkillType Skill) { return GetMapOfSkill(CraftLevelModifier, Skill); };
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetUseLevelModifier(ESkillType Skill) { return GetMapOfSkill(UseLevelModifier, Skill); };
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetHarvestLevel(EHarvestType Type) { return HarvestLevels.Contains(Type) ? HarvestLevels[Type] : 0; };
	UFUNCTION(BlueprintCallable, BlueprintPure)
	EAssemblyComponentType GetComponentType() { return ComponentType; };
};

/*
UCLASS(Blueprintable)
class QUINT_API UEquipment : public UItem, public ITool
{
	GENERATED_BODY()
protected:
	EEquipmentSlot Slot = EEquipmentSlot::ES_WEAPON;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TMap<EAssemblyComponentType, UAssemblyComponent*>Components;
public:
	UDataTable* EquipmentDataTable;
	UEquipment();
	virtual void Use(AActor* On) {};
	//To be called after initial creation
	UFUNCTION(BlueprintCallable)
	bool InitComponents(TMap<EAssemblyComponentType, UAssemblyComponent*> InitComponents);
	//virtual bool InitComponents_Implementation(TMap<EAssemblyComponentType, UAssemblyComponent*> InitComponents);
	virtual EEquipmentSlot GetEquipmentSlot_Implementation() { return Slot; }
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable,Blueprintpure)
	TMap<EAssemblyComponentType, UAssemblyComponent*> GetComponents();
	TMap<EAssemblyComponentType, UAssemblyComponent*> GetComponents_Implementation();

	virtual int GetHarvestLevelOfType_Implementation(EHarvestType Type);
	virtual int GetRequiredUseLevel_Implementation(EHarvestType Type);
};
*/
/*
UEquipment::UEquipment() {
	ConstructorHelpers::FObjectFinder<UTexture2D> TextureFinder(TEXT("/Game/UserInterface/Icons/axe.axe"));
	if (TextureFinder.Succeeded())
		ImageTexture = TextureFinder.Object;
	IndexId = 2;
	MaxStackSize = 1;
}


bool UEquipment::InitComponents(TMap<EAssemblyComponentType, UAssemblyComponent*> InitComponents){

	for (TPair<EAssemblyComponentType,UAssemblyComponent*> &current : Components) {
		if (InitComponents.Contains(current.Key)) {
			current.Value = *InitComponents.Find(current.Key);
		}
		else {
			Components.Empty();
			return false;
		}
	}
	for (TPair<EAssemblyComponentType, UAssemblyComponent*> &current : Components) {
		if (InitComponents.Contains(current.Key)) {
			InitComponents.Remove(current.Key);
		}
	}

	return true;
}

TMap<EAssemblyComponentType, UAssemblyComponent*> UEquipment::GetComponents_Implementation(){
	return Components;
}

int UEquipment::GetHarvestLevelOfType_Implementation(EHarvestType Type)
{
	int highest = 0;
	for (TPair<EAssemblyComponentType, UAssemblyComponent*> &current : Components) {
		int currentValue = current.Value->GetHarvestLevel(Type);
		if (currentValue > highest) {
			highest = currentValue;
		}
	}
	return highest;
}

int UEquipment::GetRequiredUseLevel_Implementation(EHarvestType Type)
{
	return 0;
}
*/