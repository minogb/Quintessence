// Fill out your copyright notice in the Description page of Project Settings.

#include "ResourceNode.h"
#include "Engine/World.h"
#include "UnrealNetwork.h"
#include "Avatar.h"
#include "Item.h"
#include "Item_World.h"
#include "QuintPlayerController.h"
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
	//TODO: remove this
	Rewards.Add(FResourceReward(UItem::StaticClass(),1,1,50));
	Rewards.Add(FResourceReward(UItem::StaticClass(),1,1,100));
	HarvestLevel = 1;
	HarvestType = EHarvestType::HT_MINING;
}
void AResourceNode::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const{
	DOREPLIFETIME(AResourceNode, Harvesters);
}
bool AResourceNode::CanPlayerHarvest(AAvatar * Player){
	if (IsValid(Player)) {
		return Player->GetHighestToolLevelOfType(HarvestType) >= HarvestLevel;
	}
	return false;
}
void AResourceNode::HarvestThis(AAvatar * Player){
	if(CanPlayerHarvest(Player) && GetWorld()){
		Harvesters.Add(FPlayerHarvestedStruct(Player,GetWorld()->GetRealTimeSeconds()));
		GivePlayerReward(Player);
	}
}

void AResourceNode::GivePlayerReward(AAvatar * Player){
	AQuintPlayerController* pc = Player->GetQuintController();
	TArray<UItem*> Reward = GetPlayerReward(Player);
	for(int i = 0; i < Reward.Num(); i++){
		if(Reward.IsValidIndex(i)){
			pc->AddItemToInventory(Reward[i]);
			if(IsValid((UObject*)Reward[i]) && Reward[i]->GetStackSize() > 0){
				SpawnWorldItem(Reward[i], Player);
			}
		}
	}
}

void AResourceNode::SpawnWorldItem(UItem * Item, AActor * ToOwn){
	//if item still valid drop into world
	FTransform actorTranform = ToOwn->GetActorTransform();
	actorTranform.SetScale3D(FVector(1));
	AItem_World* newItem = GetWorld()->SpawnActorDeferred<AItem_World>(AItem_World::StaticClass(),actorTranform, ToOwn);
	newItem->InitItem(Item);
	newItem->FinishSpawning(actorTranform);
}
TArray<UItem*> AResourceNode::GetPlayerReward(AAvatar * Player){
	TArray<UItem*> retVal = TArray<UItem*>();
	//Generate item types/amount
	for(int i =  0; i < Rewards.Num(); i++){
		if(Rewards.IsValidIndex(i)){
			int Result = FMath::FRandRange(0,100);
			//TODO: add luck boost for chance and extra
			if(Result <= Rewards[i].RewardChance){/*
				retVal.Add(
					UItem::CREATE_ITEM(
						Player,UItem::StaticClass(),
						FMath::FRandRange(
							Rewards[i].MinCount,Rewards[i].MaxCount
						)
					)
				);*/
				retVal.Add(NewObject<UItem>(Player, Rewards[i].ItemReward));
			}
		}
	}
	return retVal;
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

bool AResourceNode::IsValidTask(EInteractionType Task, AAvatar * Player){
	if (!IsValid(Player)) {
		return false;
	}
	if (!CanPlayerHarvest(Player))
		return false;
	if((GetAvaliableTasks() & Task) == Task){
		for(int i = 0; i < Harvesters.Num(); i++){
			//has player already harvested?
			if(Harvesters.IsValidIndex(i) && Harvesters[i].Player == Player)
				return false;
		}
		//player has not harvested yet
		return true;
	}
	return false;
}