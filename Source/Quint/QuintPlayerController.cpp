// Fill out your copyright notice in the Description page of Project Settings.

#include "QuintPlayerController.h"
#include "Engine/World.h"
#include "Avatar.h"
#include "PlayerVessel.h"
#include "Engine/GameEngine.h"
#include "AvatarController.h"
#include "UnrealNetwork.h"
#include "Item_World.h"
#include "Item.h"
#include "Equipment.h"
#include "Tool.h"
#include "Blueprint/UserWidget.h"
#include "Engine/ActorChannel.h"
#include "QuintGameMode.h"
#include "CraftingInfo.h"
#include "CraftingWidgetInterface.h"

void AQuintPlayerController::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AQuintPlayerController, PlayerAvatar);
	DOREPLIFETIME(AQuintPlayerController, Inventory);
	DOREPLIFETIME(AQuintPlayerController, Equipment);
}
bool AQuintPlayerController::ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags)
{
	bool WroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);
	for (int i = 0; i < InventorySizeMax; i++) {
		if (Inventory.IsValidIndex(i) && Inventory[i]) {
			WroteSomething |= Channel->ReplicateSubobject((UObject*)Inventory[i], *Bunch, *RepFlags);
		}
	}

	return WroteSomething;
}

void AQuintPlayerController::DoItemAction(UItem* Item, EItemAction Action) {
	switch (Action) {
	case EItemAction::IA_EQUIP:
		EquipItem(Item);
		break;
	case EItemAction::IA_UNEQUIP:
		UnEquipItem(Item);
		break;
	case EItemAction::IA_DROP:
		DropItem(Item);
		break;
	case EItemAction::IA_USE:
		break;
	default:
		break;
	}
}

void AQuintPlayerController::EquipItem(UItem * Item){
	int index = GetIndexOfItem(Item);
	if (index > -1)
		EquipItem(index);
}

void AQuintPlayerController::EquipItem_Implementation(int Slot){
	if (!Inventory.IsValidIndex(Slot))
		return;
	UEquipment* item = Cast<UEquipment>(Inventory[Slot]);
	if (IsValid(item) && item->GetSlot() != EEquipmentSlot::ES_NONE) {
		const EEquipmentSlot slot = item->GetSlot();
		UnEquipItem(slot);
		if (!IsValid(Equipment.Get(slot))) {
			Inventory[Slot] = NULL;
			Equipment.SetEquipment(item);
		}
	}
}
bool AQuintPlayerController::EquipItem_Validate(int Slot){
	return true;
}
void AQuintPlayerController::UnEquipItem_Implementation(EEquipmentSlot Slot){
	UItem* item = GetEquipment(Slot);
	AddItemToInventory(item);
	if (!IsValid(item)) {
		Equipment.SetEquipment(NULL,Slot);
	}

}
bool AQuintPlayerController::UnEquipItem_Validate(EEquipmentSlot Slot)
{
	return true;
}
void AQuintPlayerController::UnEquipItem(UItem * Item){
	UEquipment* item = Cast<UEquipment>(Item);
	if (IsValid(item))
		UnEquipItem(item->GetSlot());
}
void AQuintPlayerController::StartCraftingItem_Implementation(AActor* AtLocation, FCraftingStruct Recipe, int CraftingAmount){
	UCraftingInfo* info = NewObject<UCraftingInfo>();
	info->InitObject(Recipe, CraftingAmount);
	Server_SetGoalAndAction(AtLocation, EInteractionType::Use, info);
}//here
int AQuintPlayerController::GetIndexOfItem(UItem * Item){
	for (int index = 0; index < Inventory.Num(); index++) {
		if (Inventory.IsValidIndex(index)) {
			if (Inventory[index] == Item) {
				return index;
			}
		}
	}
	return -1;
}
AQuintPlayerController::AQuintPlayerController(){
	SetReplicates(true);
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	Inventory.Init(nullptr,InventorySizeMax);
}

bool AQuintPlayerController::SetPlayerAvatar(AAvatar * avatar){
	if(HasAuthority()){
		PlayerAvatar = avatar;
		return PlayerAvatar != nullptr;
	}
	return false;
}

void AQuintPlayerController::AddItemToInventory(AItem_World* ItemWorld){
	AddItemToInventory(ItemWorld->ItemReference);
	if (!IsValid(ItemWorld->ItemReference))
		ItemWorld->Destroy(true);
}

void AQuintPlayerController::AddItemToInventory(UItem*& Item){
	if(!IsValid(Item))
		return;
	for(int i = 0; i < InventorySizeMax; i++){
		if(IsValid(Inventory[i])){
			Inventory[i]->Combine(Item);		
		}
		//all items added to inventory
		if(!IsValid(Item))
			break;
	}

	for (int i = 0; IsValid(Item) && Item->GetStackSize() > 0 && i < InventorySizeMax; i++) {
		if (!IsValid(Inventory[i])) {
			Inventory[i] = Item;
			Item = nullptr;
			break;
		}
	}
}
void AQuintPlayerController::AddItemToInventory(TSubclassOf<UItem> ItemClass, int Quantity){
	UItem* item = NewObject<UItem>(this,ItemClass);
	item->SetStackSize(Quantity);
	AddItemToInventory(item);
}
void AQuintPlayerController::BeginPlay(){
	Super::BeginPlay();
}

void AQuintPlayerController::SetDestinationOrGoal(){
	FHitResult Hit;
	bool GotGoal = false;
	if(GetHitResultUnderCursor(ECC_Interactable, false, Hit)){
		AActor* hitActor = Hit.GetActor();
		if(IsValid(PlayerAvatar) && IsValid(hitActor) && hitActor != PlayerAvatar){
			if (IsValid(hitActor) && hitActor->GetClass()->ImplementsInterface(UInteractable::StaticClass())) {
				Server_SetGoalAndAction(hitActor,(EInteractionType)IInteractable::Execute_GetDefaultTask(hitActor));
				GotGoal = true;
			}
		}
	}
	if (!GotGoal && GetHitResultUnderCursor(ECC_Floor, false, Hit)){
		float const Distance = FVector::Dist(Hit.Location, GetPawn()->GetActorLocation());
		Server_SetDestination(Hit.ImpactPoint);
		GotGoal = true;
	}
	if (GotGoal) {
		DisplayUI(NULL);
	}
}

void AQuintPlayerController::DropItem_Implementation(int Slot) {
	if (Inventory.IsValidIndex(Slot) && IsValid(Inventory[Slot]) && IsValid(GetPlayerAvatar())) {
		FTransform actorTranform = GetPlayerAvatar()->GetActorTransform();
		actorTranform.SetScale3D(FVector(1));
		AItem_World* newItem = GetWorld()->SpawnActorDeferred<AItem_World>(AItem_World::StaticClass(), actorTranform, this);
		newItem->InitItem(Inventory[Slot]);
		Inventory[Slot] = NULL;
		newItem->FinishSpawning(actorTranform);

	}

}

bool AQuintPlayerController::DropItem_Validate(int Slot){
	return true;
}

void AQuintPlayerController::DisplayUI_Implementation(TSubclassOf<UUserWidget> WidgetClass, AActor* WorldReference){

	if (IsValid(ActiveWidget)) {
		ActiveWidget->RemoveFromParent();
		ActiveWidget = NULL;
	}
	if(IsValid(WidgetClass))
		ActiveWidget = CreateWidget<UUserWidget>(this, WidgetClass);
	if (IsValid(ActiveWidget)) {
		ActiveWidget->AddToViewport();
	}
	if (IsValid(ActiveWidget) && ActiveWidget->GetClass()->ImplementsInterface(UCraftingWidgetInterface::StaticClass())) {
		ICraftingWidgetInterface::Execute_SetWorldReference(ActiveWidget, WorldReference); 
	}
}

void AQuintPlayerController::Client_DisplayUI_Implementation(TSubclassOf<class UUserWidget> WidgetClass, AActor* WorldReference){
	DisplayUI(WidgetClass, WorldReference);
}
bool AQuintPlayerController::CanCraftRecipe(FCraftingStruct Recipe) {
	for (FItemCraftingStruct &current : Recipe.Input) {
		if (!HasItem(current.Item, current.Count))
			return false;
	}
	return HasRoom(Recipe.Output.Item,Recipe.Output.Count);
}
bool AQuintPlayerController::HasItem(TSubclassOf<UItem> Item, int Quantity){
	for (UItem*current : Inventory) {
		if (IsValid(current) && current->IsA(Item)) {
			Quantity -= current->GetStackSize();
		}
		if (Quantity <= 0)
			return true;
	}
	return false;
}
bool AQuintPlayerController::ConsumeItem(TSubclassOf<UItem> Item, int Quantity, bool FullConsumption) {
	TArray<int> Indexs;
	int currentQuantity = Quantity;
	for (int i = 0; i < Inventory.Num(); i++) {
		if (Inventory.IsValidIndex(i) && IsValid(Inventory[i]) && Inventory[i]->IsA(Item)) {
			Indexs.Add(i);
			currentQuantity -= Inventory[i]->GetStackSize();
			if (currentQuantity <= 0)
				break;
		}
	}
	if (FullConsumption && currentQuantity > 0)
		return false;
	currentQuantity = Quantity;
	for (int current : Indexs) {
		if (Quantity - Inventory[current]->GetStackSize() >= 0) {
			Quantity -= Inventory[current]->GetStackSize();
			Inventory[current] = NULL;
		}
		else {
			Quantity -= Inventory[current]->GetStackSize();
			Inventory[current]->SetStackSize(Quantity*-1);
			return true;
		}
	}
	return false;

}
bool AQuintPlayerController::HasRoom(UItem * Item){
	return IsValid(Item) && HasRoom(Item->GetClass(),Item->GetStackSize());
}
bool AQuintPlayerController::HasRoom(TSubclassOf<UItem> Item, int Quantity){
	for (UItem* current : Inventory) {
		if (!IsValid(current))
			return true;
		else if(current->IsA(Item)){
			Quantity -= current->GetStackSize() - current->GetMaxStackSize();
			if (Quantity <= 0)
				return true;
		}
	}
	return false;
}
void AQuintPlayerController::Server_CraftRecipe_Implementation(FName RecipeTableRowName){
	//TODO  check if by a crafting area 
	//TODO check if has room for output
	//TODO check if has requried tool
	AQuintGameMode* gm = Cast<AQuintGameMode>(GetWorld()->GetAuthGameMode());
	if (IsValid(gm)) {
		FCraftingStruct recipe;
		if (gm->GetOutputofRecipe(RecipeTableRowName, recipe)) {
			if (CanCraftRecipe(recipe)) {
				for (FItemCraftingStruct &current : recipe.Input) {
					ConsumeItem(current.Item, current.Count, true);
				}
				AddItemToInventory(recipe.Output.Item, recipe.Output.Count);
			}
			else {
			}
		}
		
	}
}
bool AQuintPlayerController::CraftRecipe(FCraftingStruct Recipe){
	if (HasAuthority() && CanCraftRecipe(Recipe)) {
		for (FItemCraftingStruct &current : Recipe.Input) {
			ConsumeItem(current.Item, current.Count, true);
		}
		AddItemToInventory(Recipe.Output.Item, Recipe.Output.Count);
		return true;
	}
	return false;

}
void AQuintPlayerController::DropItem(UItem * Item){
	int index = GetIndexOfItem(Item);
	if(index > -1)
		DropItem(index);
}

//TODO: check equiped weapon
int AQuintPlayerController::GetHighestToolLevelOfType(EHarvestType Type){
	int highest = 0;
	highest = GetEquipmentToolLevelOfType(Type);
	if (highest > 0)
		return highest;
	for (int i = 0; i < Inventory.Num(); i++) {
		if (Inventory.IsValidIndex(i) && IsValid(Inventory[i])) {
			if (Inventory[i]->GetClass()->ImplementsInterface(UTool::StaticClass())) {
				int level = ITool::Execute_GetHarvestLevelOfType(Inventory[i], Type);
				if (highest < level) {
					highest = level;
				}
			}
		}
	}
	return highest;
}
int AQuintPlayerController::GetEquipmentToolLevelOfType(EHarvestType Type) {

	UEquipment* item = NULL;
	if (IsValid(item = GetEquipment(EEquipmentSlot::ES_WEAPON))) {
		if (item->GetClass()->ImplementsInterface(UTool::StaticClass()))
			return ITool::Execute_GetHarvestLevelOfType(item, Type);
	}
	if (IsValid(item = GetEquipment(EEquipmentSlot::ES_SHEILD))) {
		if (item->GetClass()->ImplementsInterface(UTool::StaticClass()))
			return ITool::Execute_GetHarvestLevelOfType(item, Type);
	}
	if (IsValid(item = GetEquipment(EEquipmentSlot::ES_RING))) {
		if (item->GetClass()->ImplementsInterface(UTool::StaticClass()))
			return ITool::Execute_GetHarvestLevelOfType(item, Type);
	}
	if (IsValid(item = GetEquipment(EEquipmentSlot::ES_GLOVES))) {
		if (item->GetClass()->ImplementsInterface(UTool::StaticClass()))
			return ITool::Execute_GetHarvestLevelOfType(item, Type);
	}
	return 0;
}
UEquipment * AQuintPlayerController::GetEquipment(EEquipmentSlot EquipmentType)
{
	return Equipment.Get(EquipmentType);
}
bool AQuintPlayerController::IsValidLocation(FVector location){
	return !location.Equals(FVector(0),1);
}

void AQuintPlayerController::Server_SetDestination_Implementation  (FVector Location){
	if(PlayerAvatar && HasAuthority() && IsValidLocation(Location)){
		PlayerAvatar->SetLocationGoal(Location);
	}
}
void AQuintPlayerController::Server_SetGoalAndAction_Implementation (AActor * Goal, EInteractionType Action, UObject* UseThis){
	
	if(PlayerAvatar && HasAuthority() && Goal){
		PlayerAvatar->SetGoalAndAction(Goal, Action, UseThis);
	}
}

bool AQuintPlayerController::Server_SetDestination_Validate (FVector Location){
	return true;
}
bool AQuintPlayerController::Server_SetGoalAndAction_Validate (AActor * Goal, EInteractionType Action, UObject* UseThis){
	return true;
}

void AQuintPlayerController::SetupInputComponent(){
	// set up gameplay key bindings
	Super::SetupInputComponent();
	InputComponent->BindAction("SetDestination", IE_Released, this, 
		&AQuintPlayerController::SetDestinationOrGoal);
}