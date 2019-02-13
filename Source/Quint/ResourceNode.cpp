// Fill out your copyright notice in the Description page of Project Settings.

#include "ResourceNode.h"
#include "Engine/World.h"
#include "UnrealNetwork.h"
#include "Components/BoxComponent.h"

AResourceNode::AResourceNode()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 1;
	SetReplicates(true);
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	if(BoxComponent){
		BoxComponent->InitBoxExtent(FVector(64.f));
		SetRootComponent(BoxComponent); 
		BoxComponent->SetCollisionResponseToChannel(ECC_Interactable,ECR_Block);
		BoxComponent->SetCollisionResponseToChannel(ECC_Pawn,ECR_Ignore);
		BoxComponent->SetVisibility(true);
		BoxComponent->bHiddenInGame = false;
	}
}
void AResourceNode::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const{
	DOREPLIFETIME(AResourceNode, Harvesters);
}
void AResourceNode::HarvestThis(AAvatar * Player){
	//TODO: Add can actually harvest this!
	if(GetWorld())
		Harvesters.Add(FPlayerHarvestedStruct(Player,GetWorld()->GetRealTimeSeconds()));
}

void AResourceNode::BeginPlay(){
	Super::BeginPlay();
	
}

void AResourceNode::RemovePlayersFromHarvesters(){
	float CurrentTime = GetWorld()->GetRealTimeSeconds();
	for(int i= 0; i < Harvesters.Num(); i++){
		if(Harvesters.IsValidIndex(i)){
			//TODO REMOVE VALID PLAYER CHECK WHEN WE GET PLAYER TRACKING
			if(!IsValid((UObject*)Harvesters[i].Player) || Harvesters[i].TimeHarvested + TimeToReset <=CurrentTime){
				Harvesters.RemoveAt(i,1,false);
			}
		}
	}
	Harvesters.Shrink();
}

void AResourceNode::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
	if(HasAuthority()){
		RemovePlayersFromHarvesters();
	}
}

float AResourceNode::GetSize()
{
	return BoxComponent->GetScaledBoxExtent().X;
}

