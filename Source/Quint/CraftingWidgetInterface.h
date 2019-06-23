#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CraftingWidgetInterface.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI)
class  UCraftingWidgetInterface : public UInterface {
	GENERATED_BODY()
};
class QUINT_API ICraftingWidgetInterface {
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent)
	void SetWorldReference(AActor* WorldActor);
	virtual void SetWorldReference_Implementation(AActor* WorldActor) {};
};