// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InteractableInterface.h"
#include "QuintCharacter.generated.h"
UCLASS(Blueprintable)
class AQuintCharacter : public ACharacter, public IInteractableInterface
{
	GENERATED_BODY()

protected:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRepHealth)
	int32 Health;
public:
protected:
	UFUNCTION()
	void OnRepHealth();
	//---------------------------------------Animations--------------------------------------------
	UFUNCTION(BlueprintNativeEvent)
	void BpPrimaryAttackAnimation();

	UFUNCTION(BlueprintNativeEvent)
	void BpBlockAnimation();
	
	UFUNCTION(BlueprintNativeEvent)
	void BpHitAnimation();
	
public:
	AQuintCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

	FORCEINLINE class AQuintPlayerState* GetPlayerState();

	virtual EInteractionType GetDefaultTask() override;
	virtual int32 GetAvaliableTasks() override { return Move_Here | Follow | Trade; }
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount,
		struct FDamageEvent const & DamageEvent,
		class AController * EventInstigator,
		AActor * DamageCauser) override;
	//---------------------------------------Replicate---------------------------------------------
	//---------------------------------------Animations--------------------------------------------
	UFUNCTION(NetMulticast,Unreliable)
	void ReplicatePrimaryAttackAnimation();

	UFUNCTION(NetMulticast,Unreliable)
	void ReplicateBlockAnimation();
	
	UFUNCTION(NetMulticast,Unreliable)
	void ReplicateHitAnimation();
	

};

