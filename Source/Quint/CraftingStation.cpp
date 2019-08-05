// Fill out your copyright notice in the Description page of Project Settings.


#include "CraftingStation.h"
#include "Components/BoxComponent.h"
#include "QuintPlayerController.h"
#include "Avatar.h"
#include "Blueprint/UserWidget.h"
#include "CraftingInfo.h"
#include "Engine/GameEngine.h"
// Sets default values
ACraftingStation::ACraftingStation(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	NavigationHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Navigation Hit Box"));
	if (NavigationHitBox) {
		NavigationHitBox->InitBoxExtent(FVector(WorldSize*.75, WorldSize*.75, WorldSize));
		NavigationHitBox->SetCollisionResponseToAllChannels(ECR_Block);
		NavigationHitBox->SetCollisionResponseToChannel(ECC_ProjectileBlock, ECollisionResponse::ECR_Ignore);
		NavigationHitBox->SetVisibility(true);
		NavigationHitBox->bHiddenInGame = false;
		NavigationHitBox->SetCanEverAffectNavigation(true);
		SetRootComponent(NavigationHitBox);

	}
	ClickBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ClickBox"));
	if (ClickBox) {
		ClickBox->InitBoxExtent(FVector(WorldSize*1.1));
		ClickBox->SetCollisionResponseToAllChannels(ECR_Ignore);
		ClickBox->SetCollisionResponseToChannel(ECC_Interactable, ECR_Block);
		ClickBox->SetVisibility(true);
		ClickBox->bHiddenInGame = false;
		ClickBox->SetCanEverAffectNavigation(false);
		FAttachmentTransformRules rules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
		ClickBox->AttachToComponent(NavigationHitBox, rules);
	}
	bNetLoadOnClient = false;
	bNetLoadOnClient = false;
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 1;
	SetReplicates(true);

}

bool ACraftingStation::UseThis_Implementation(UObject * With, UObject * Source){
	UCraftingInfo* cInfo = Cast<UCraftingInfo>(With);
	AAvatar* PlayerAvatar = Cast<AAvatar>(Source);
	AQuintPlayerController* Player = NULL;
	if (IsValid(PlayerAvatar)) {
		
		Player = PlayerAvatar->GetQuintController();
	}
	if (IsValid(Player)) {
		if (IsValid(cInfo)) {
			//TODO validate recipe
			if (Player->CraftRecipeWithInfo(cInfo)){
				return cInfo->GetCraftingAmount() > 0 && Player->CanCraftRecipe(cInfo->GetCraftingRecipe());
			}
			else
				return false;
		}
		else {
			Player->Client_DisplayUI(WidgetClass, this);
		}
		return true;
	}
	return false;
}

float ACraftingStation::GetSize_Implementation(){
	return WorldSize;
}
EInteractionType ACraftingStation::GetDefaultTask_Implementation()
{
	return EInteractionType::Use;
}
bool ACraftingStation::IsValidTask_Implementation(TEnumAsByte<EInteractionType> Task, AAvatar * Player)
{
	return true;
}
// Called when the game starts or when spawned
void ACraftingStation::BeginPlay(){
	Super::BeginPlay();
	
}

// Called every frame
void ACraftingStation::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

}

