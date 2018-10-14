// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PawnInterface.h"
#include "PlayerCharacter.generated.h"

UCLASS(Blueprintable)
class QUINT_API APlayerCharacter : public ACharacter, public IPawnInterface
{
	GENERATED_BODY()


protected:
	static const float MIN_MOVE_DISTANCE;
	//UPROPERTY(ReplicatedUsing = OnRepHealth)
	int32 Health;
	/** Top down camera */
	//in the future add third person? or other
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this pawn's properties
	APlayerCharacter();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void MovePawnToLocationOrActor(const FVector DestLocation, AActor* DestActor) override;
	
};
