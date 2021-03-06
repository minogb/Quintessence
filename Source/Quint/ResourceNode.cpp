// Fill out your copyright notice in the Description page of Project Settings.

#include "ResourceNode.h"
#include "Engine/World.h"
#include "UnrealNetwork.h"
#include "Avatar.h"
#include "Item.h"
#include "Item_World.h"
#include "QuintPlayerController.h"
#include "Components/BoxComponent.h"

#define PrintToScreen(x) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, FString(x));}

AResourceNode::AResourceNode(){
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 1;
	SetReplicates(true);
	NavigationHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Navigation Hit Box"));
	if (NavigationHitBox) {
		NavigationHitBox->InitBoxExtent(FVector(WorldSize*.75, WorldSize*.75, WorldSize));
		NavigationHitBox->SetCollisionResponseToAllChannels(ECR_Block);
		NavigationHitBox->SetCollisionResponseToChannel(ECC_ProjectileBlock, ECollisionResponse::ECR_Ignore);
		NavigationHitBox->SetVisibility(true);
		NavigationHitBox->bHiddenInGame = false;
		NavigationHitBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		NavigationHitBox->SetCanEverAffectNavigation(true);
		SetRootComponent(NavigationHitBox);

	}
	ClickBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ClickBox"));
	if(ClickBox){
		ClickBox->InitBoxExtent(FVector(WorldSize*1.1));
		ClickBox->SetCollisionResponseToAllChannels(ECR_Ignore);
		ClickBox->SetCollisionResponseToChannel(ECC_Interactable,ECR_Block);
		ClickBox->SetVisibility(true);
		ClickBox->bHiddenInGame = false;
		ClickBox->SetCanEverAffectNavigation(false);
		NavigationHitBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		FAttachmentTransformRules rules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
		ClickBox->AttachToComponent(NavigationHitBox, rules);
	}
	bNetLoadOnClient = false;
}
void AResourceNode::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const{
	DOREPLIFETIME(AResourceNode, Harvesters);
}
bool AResourceNode::CanPlayerHarvest(AAvatar * Player){
	if (IsValid(Player)) {
		if (Player->GetSkillLevel(RequiredLevel.Skill) >= RequiredLevel.Level) {
			return Player->GetHighestToolLevelOfType(HarvestType) >= HarvestLevel;
		}
	}
	return false;
}
void AResourceNode::HarvestThis(AAvatar * Player){
	if(CanPlayerHarvest(Player) && GetWorld()){
		Harvesters.Add(FPlayerHarvestedStruct(Player,GetWorld()->GetRealTimeSeconds()));
		GivePlayerReward(Player);
	}
}

float AResourceNode::GetHarvestSpeed(){
	return 1.f;
}

void AResourceNode::GivePlayerReward(AAvatar * Player){
	AQuintPlayerController* pc = Player->GetQuintController();
	TArray<FResourceReward> Reward = GetPlayerReward(Player);
	for(int i = 0; i < Reward.Num(); i++){
		if(Reward.IsValidIndex(i)){
			UItem* item =  NewObject<UItem>(Player, Reward[i].ItemReward);
			item->SetStackSize(Reward[i].ItemQuantity);
			PrintToScreen(FString::FromInt(Reward[i].ItemQuantity));
			pc->AddItemToInventory(item);
			pc->AddExperience(Reward[i].ExpReward.Skill, Reward[i].ExpReward.Exp);
			if(IsValid((UObject*)item) && item->GetStackSize() > 0){
				SpawnWorldItem(item, Player);
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
TArray<FResourceReward> AResourceNode::GetPlayerReward(AAvatar * Player){
	TArray<FResourceReward> retVal = TArray<FResourceReward>();
	//Generate item types/amount
	for(int i =  0; i < Rewards.Num(); i++){
		if(Rewards.IsValidIndex(i)){
			int Result = FMath::FRandRange(0,100);
			//TODO: add luck boost for chance and extra
			if(Result <= Rewards[i].RewardChance && IsValid(Rewards[i].Reward.ItemReward)){
				FResourceReward current = Rewards[i].Reward;
				current.ItemQuantity = FMath::RandRange(Rewards[i].MinCount, Rewards[i].MaxCount);
				retVal.Add(current);
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


float AResourceNode::GetSize_Implementation()
{
	return WorldSize;
}

bool AResourceNode::IsValidTask_Implementation(TEnumAsByte<EInteractionType> Task, AAvatar * Player){
	if (!IsValid(Player)) {
		return false;
	}
	if (!CanPlayerHarvest(Player))
		return false;

	if(IInteractable::IsValidTask_Implementation(Task,Player)){
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