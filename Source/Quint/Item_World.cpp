// Fill out your copyright notice in the Description page of Project Settings.

#include "Item_World.h"
#include "Components/CapsuleComponent.h"
#include "Item.h"
#include "UnrealNetwork.h"

// Sets default values
AItem_World::AItem_World()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	if(CapsuleComponent){
		CapsuleComponent->InitCapsuleSize(30.f, 30.f);
		SetRootComponent(CapsuleComponent); 
		CapsuleComponent->SetCollisionResponseToChannel(ECC_Interactable,ECR_Block);
		CapsuleComponent->SetCollisionResponseToChannel(ECC_Pawn,ECR_Ignore);
		CapsuleComponent->SetVisibility(true);
		CapsuleComponent->bHiddenInGame = false;
	}
	ItemReference = NewObject<UItem>();
	this->SetReplicates(true);
}

void AItem_World::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );
	DOREPLIFETIME(AItem_World, ItemReference);
}
// Called when the game starts or when spawned
void AItem_World::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItem_World::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem_World::CombineWith(UItem*& item){
	//if empty item slot passed, just give whole sale
	if(!IsValid(item) || !item){
		item = ItemReference;
		ItemReference = nullptr;
	}
	//Otherwise try to combien the two items
	else{
		item->Combine(ItemReference);
	}
	//If we no longer have anything to give, destroy us
	if(!IsValid(ItemReference)){
		ItemReference = nullptr;
		this->Destroy(true);
	}
}

