// Fill out your copyright notice in the Description page of Project Settings.


#include "Dagger.h"
#include "Interfaces/ComponentInterface.h"
UItem * UDagger::GetComponent_Implementation(EAssemblyComponentType Type){
	switch (Type) {
		case EAssemblyComponentType::ECT_S_BLADE:
			return SmallBlade;
		case EAssemblyComponentType::ECT_S_GRIP:
			return ShortGrip;
		case EAssemblyComponentType::ECT_S_POMMEL:
			return SmallPommel;
	}
	return nullptr;
}

bool UDagger::SetComponent_Implementation(UItem * Item){
	EAssemblyComponentType type = EAssemblyComponentType::ECT_NONE;
	if (IsValid(Item) && Item->GetClass()->ImplementsInterface(UComponentInterface::StaticClass())) {
		EAssemblyComponentType type = IComponentInterface::Execute_GetComponentSlot(Item);
	}
	switch (type) {
		case EAssemblyComponentType::ECT_S_BLADE:
			SmallBlade = Item;
			return true;
		case EAssemblyComponentType::ECT_S_GRIP:
			ShortGrip = Item;
			return true;
		case EAssemblyComponentType::ECT_S_POMMEL:
			SmallPommel = Item;
			return true;
	}

	return false;
}
