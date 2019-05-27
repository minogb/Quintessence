// Fill out your copyright notice in the Description page of Project Settings.

#include "Item_World.h"
#include "Components/BoxComponent.h"
#include "Item.h"
#include "UnrealNetwork.h"

// Sets default values
AItem_World::AItem_World()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	if(BoxComponent){
		BoxComponent->InitBoxExtent(FVector(30.f));
		SetRootComponent(BoxComponent); 
		BoxComponent->SetCollisionResponseToChannel(ECC_Interactable,ECR_Block);
		BoxComponent->SetCollisionResponseToChannel(ECC_Pawn,ECR_Ignore);
		BoxComponent->SetVisibility(true);
		BoxComponent->bHiddenInGame = false;
	}
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
	if(!HasAuthority())
		return;
	if(!IsValid(ItemReference)){
		Destroy(true);
	}

	//If we no longer have anything to give, destroy us
	if (!IsValid(ItemReference)) {
		this->Destroy(true);
	}
}

// Called every frame
void AItem_World::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
}
//Depricate
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

void AItem_World::InitItem(UItem * item){
	if(HasAuthority() && !IsValid(ItemReference)){
		ItemReference = item;
		//TODO: SET mesh here
	}
}