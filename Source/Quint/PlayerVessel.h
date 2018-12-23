// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerVessel.generated.h"

UCLASS()
class QUINT_API APlayerVessel : public APawn
{
	GENERATED_BODY()

public:
	//in the future add third person? or other
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;
	// Sets default values for this character's properties
	APlayerVessel();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	bool IsPanning = false;
	float PanRotationSpeed = 10.f;
	FVector2D LockedMousePos = FVector2D();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	AActor* PlayerAvatar;
	void AttachToAvatar();
	void PressPan();
	void ReleasePan();
	void SetPanning(bool Panning);
	void MoveMouseX(float Val);
	void MoveMouseY(float Val);
};