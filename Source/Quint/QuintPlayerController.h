#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interfaces/Interactable.h"
#include "Enumerations.h"
#include "EquipmentStructure.h"
#include "SkillStructure.h"
#include "CraftingInfo.h"
#include "QuintPlayerController.generated.h"
#define ECC_Interactable ECC_GameTraceChannel1
#define ECC_Floor ECC_GameTraceChannel2

class UAssembledEquipment;
class FJsonObject;
UCLASS()
class QUINT_API AQuintPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	//Max Item Slots a palyer has
	int InventorySizeMax = 30;
	//Players inventory slots
	UPROPERTY(Replicated)
	TArray<class UItem*> Inventory;
	//Total amount of expereince in a skill
	UPROPERTY(Replicated)
	FPlayerSkilllLevelStruct SkillExperience;
	//The players equiped items
	UPROPERTY(Replicated)
	FEquipmentStruct Equipment;
	//The reference to the player avatar, the GetPawn is just
	//a camera manager basically
	UPROPERTY(Replicated)
	class AAvatar* PlayerAvatar;
	//The currently displayed widget: does not count
	//always active widgets
	UPROPERTY(BlueprintReadWrite)
	UUserWidget* ActiveWidget;
	//--------------------------------------------------------
	//------------------------FUNCTIONS-----------------------
	//--------------------------------------------------------
	virtual void BeginPlay() override;

	//--------------------------------------------------------
	//--------------------------INPUT-------------------------
	//--------------------------------------------------------
	virtual void SetupInputComponent() override;

	//Player input needs to be passed to server
	void SetDestinationOrGoal();
	//Set the destination a player wants to move to
	UFUNCTION(Server, Unreliable, WithValidation)
	void Server_SetDestination(FVector Location);
	//Set destination of player if they want to move to another
	//actor with a goal in mind
	UFUNCTION(Server, Unreliable, WithValidation)
	void Server_SetGoalAndAction(AActor* Goal, EInteractionType Action, UObject* UseThis = nullptr);
	//Is it a valid location to move to?
	bool IsValidLocation(FVector location);


	//--------------------------------------------------------
	//-----------------------INVENTORY------------------------
	//--------------------------------------------------------
	//What slot in our inventory is this item?
	int GetIndexOfItem(UItem* Item);	

	//--------------------------------------------------------
	//---------------------Player Data------------------------
	//--------------------------------------------------------
	void NotifyOfLevelUp(ESkillType Skill, int Level);
public:
	void ClientWasKicked_Implementation(const FText& KickReason) override;
	//Init
	AQuintPlayerController();

	//Load player info in with json data
	void InitWithJSON(TSharedPtr<FJsonObject> InventoryJSON, TSharedPtr<FJsonObject> EquipmentJSON, TSharedPtr<FJsonObject> SkillsJSON);
	FString GetSaveJSON();
	//Replication setup
	virtual bool ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags) override;

	//Server only init of avatar
	bool SetPlayerAvatar(class AAvatar* avatar);

	//Complete action based on item
	//Usually from input of UI
	UFUNCTION(BlueprintCallable)
	void DoItemAction(UItem* Item, EItemAction Action);

	//Get player character rference
	UFUNCTION(BlueprintCallable, BlueprintPure)
	class AAvatar* GetPlayerAvatar() { return PlayerAvatar; }

	//--------------------------------------------------------
	//-----------------------INVENTORY------------------------
	//--------------------------------------------------------

	//--------------------------GETS--------------------------
	//Get size of inventory
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetInventorySize() { return InventorySizeMax; }
	//Get a slot of the inventory
	UFUNCTION(BlueprintCallable, BlueprintPure)
	class UItem* GetInventorySlot(int index) { return Inventory.IsValidIndex(index) ? Inventory[index] : nullptr; }
	//Get if we have room for item
	bool HasRoom(UItem* Item);
	//Get if we have room for item - class/Quantity
	bool HasRoom(TSubclassOf<UItem> Item, int Quantity);
	//Do we have an item of class and quantity?
	UFUNCTION(BlueprintCallable)
	bool HasItem(TSubclassOf<UItem> Item, int Quantity = 1, EEquipmentSlot EquipmentSlot = EEquipmentSlot::ES_NONE);

	//---------------------Manipulation-----------------------

	//Drop item based on reference, finds slot then drops based on slot
	void DropItem(UItem* Item);

	//Drop item in slot of inventory
	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
	void DropItem(int Slot);
	UFUNCTION(BlueprintCallable)
	void DropItem_Implementation(int Slot);
	UFUNCTION(BlueprintCallable)
	bool DropItem_Validate(int Slot);

	//Add An item to the inventory - from world
	UFUNCTION(BlueprintCallable)
	void AddItemToInventory(class AItem_World* ItemWorld);
	//Add An item to the inventory - from item reference
	void AddItemToInventory(class UItem*& Item);
	//Destroy item of class and qaunitty in our inventory
	//@FullConsumption only destroy if we have  the whole quantity
	UFUNCTION(BlueprintCallable)
	bool ConsumeItem(TSubclassOf<UItem> Item, int Quantity = 1, bool FullConsumption = true, EEquipmentSlot EquipmentSlot = EEquipmentSlot::ES_NONE);

	//------------------------Crafting------------------------

	//Craft Recipe at location and number of times to do so
	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
	void StartCraftingItem(AActor* AtLocation, FCraftingStruct Recipe, int CraftingAmount);
	void StartCraftingItem_Implementation(AActor* AtLocation, FCraftingStruct Recipe, int CraftingAmount);
	bool StartCraftingItem_Validate(AActor* AtLocation, FCraftingStruct Recipe, int CraftingAmount) { return true; }
	

	//Craft Recipe at location and number of times to do so
	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
	void CraftAssembly(TSubclassOf<UAssembledEquipment> AssemblyClass , const TArray<int>&ComponentList);
	void CraftAssembly_Implementation(TSubclassOf<UAssembledEquipment> AssemblyClass, const TArray<int>&ComponentList);
	bool CraftAssembly_Validate(TSubclassOf<UAssembledEquipment> AssemblyClass, const TArray<int>&ComponentList) { return true; }

	//Do we have the items/reqruiments for the recipe?
	UFUNCTION(BlueprintCallable)
	bool CanCraftRecipe(FCraftingStruct Recipe);

	//Craft a recipe based on table row
	UFUNCTION(BlueprintCallable)
	bool CraftRecipe(FCraftingStruct Recipe);
	//Craft recipe based on crafting data
	UFUNCTION(BlueprintCallable)
	bool CraftRecipeWithInfo(class UCraftingInfo* CraftingInfo);



	//-------------------------Equipment------------------------

	//Get highest level of tool we have in inventory and equipment
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetHighestToolLevelOfType(EHarvestType Type);

	//Get highest tool level we have equiped
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetEquipmentToolLevelOfType(EHarvestType Type);

	//Get equipment reference of type
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UItem* GetEquipment(EEquipmentSlot EquipmentType);

	//Equip item from invneotry
	UFUNCTION(Server, Reliable, WithValidation,BlueprintCallable)
	void EquipItem(int Slot);
	void EquipItem_Implementation(int Slot);
	bool EquipItem_Validate(int Slot);

	//equip item from reference
	void EquipItem(UItem* Item);

	//uniequip item from slot
	UFUNCTION(Server, Reliable, WithValidation,BlueprintCallable)
	void UnEquipItem(EEquipmentSlot Slot);
	void UnEquipItem_Implementation(EEquipmentSlot Slot);
	bool UnEquipItem_Validate(EEquipmentSlot Slot);

	//unequip item by reference
	void UnEquipItem(UItem* Item);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<UItem*> GetEquipmentAsList();

	//---------------------Player Data------------------------

	UFUNCTION(BlueprintCallable)
	void AddExperience(ESkillType Skill, int Amount);

	UFUNCTION(BlueprintCallable)
	void AddExperienceReward(TArray<FExpRewardStruct> Experience);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetSkillLevel(ESkillType Skill);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetCurrentExpInSkill(ESkillType Skill);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetTotalExpRequiredForLevel(int Level) { return FPlayerSkilllLevelStruct::GetTotalExpRequiredForLevel(Level); }

	//--------------------------------------------------------
	//-----------------------INTERFACE------------------------
	//--------------------------------------------------------

	//Tell the client to display a UI and link it to a world reference
	UFUNCTION(Client, Unreliable, BlueprintCallable)
	void Client_DisplayUI(TSubclassOf<class UUserWidget> WidgetClass, AActor* WorldReference = nullptr);
	void Client_DisplayUI_Implementation(TSubclassOf<class UUserWidget> WidgetClass, AActor* WorldReference = nullptr);

	//Tell the client to display a UI and link it to a world reference
	UFUNCTION(Client, Unreliable, BlueprintCallable)
	void Client_DisplayUIReference(UUserWidget* WidgetReference, AActor* WorldReference = nullptr);
	void Client_DisplayUIReference_Implementation(UUserWidget* WidgetReference, AActor* WorldReference = nullptr);

	//Display UI, called from server
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void DisplayUI(TSubclassOf<class UUserWidget> WidgetClass, AActor* WorldReference = nullptr);
	void DisplayUI_Implementation(TSubclassOf<class UUserWidget> WidgetClass, AActor* WorldReference = nullptr);


	//Display UI, called from server
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void DisplayUIReference(UUserWidget* WidgetReference, AActor* WorldReference = nullptr);
	void DisplayUIReference_Implementation(UUserWidget* WidgetReference, AActor* WorldReference = nullptr);
};
