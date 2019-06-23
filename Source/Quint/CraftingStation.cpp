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
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	if (BoxComponent) {
		BoxComponent->InitBoxExtent(FVector(64.f));
		SetRootComponent(BoxComponent);
		BoxComponent->SetCollisionResponseToChannel(ECC_Interactable, ECR_Block);
		BoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
		BoxComponent->SetVisibility(true);
		BoxComponent->bHiddenInGame = false;
	}
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
			if (cInfo->GetCraftingAmount() > 0 && Player->CraftRecipe(cInfo->GetCraftingRecipe())) {
				cInfo->DecrimentCraftingAmount();
				return cInfo->GetCraftingAmount() > 0 && Player->CraftRecipe(cInfo->GetCraftingRecipe());
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
	return BoxComponent->GetScaledBoxExtent().X;
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

