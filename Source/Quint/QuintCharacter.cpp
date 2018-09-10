// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "QuintCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "ServerHelper.h"
#include "Components/SkeletalMeshComponent.h"
#include "QuintPlayerState.h"

AQuintCharacter::AQuintCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	//GetCharacterMovement()->bConstrainToPlane = true;
	//GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	
	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshAsset(TEXT("SkeletalMesh'/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'"));
	if(SkeletalMeshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(SkeletalMeshAsset.Object);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//static ConstructorHelpers::FObjectFinder<UClass> AnimInstanceAsset(TEXT("/Game/Mannequin/Animations/ThirdPerson_AnimBP.ThirdPerson_AnimBP"));
	//if(AnimInstanceAsset.Succeeded())
	//	GetMesh()->SetAnimInstanceClass(AnimInstanceAsset.Object);
}

void AQuintCharacter::Tick(float DeltaSeconds){
    Super::Tick(DeltaSeconds);

	if (CursorToWorld != nullptr)	{
		if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);
		}
	}
}
AQuintPlayerState * AQuintCharacter::GetPlayerState(){
	return Cast<AQuintPlayerState>(PlayerState);
}
EInteractionType AQuintCharacter::GetDefaultTask(){
	return Attack;
	//return (GetPlayerState()->GetAttackableState() == Assailable ? Attack : Move_Here);
}
void AQuintCharacter::BeginPlay() {
	Super::BeginPlay();
}

void AQuintCharacter::ReplicatePrimaryAttackAnimation_Implementation(){
	BpPrimaryAttackAnimation();
}

void AQuintCharacter::ReplicateBlockAnimation_Implementation(){
}

void AQuintCharacter::ReplicateHitAnimation_Implementation(){
}

void AQuintCharacter::BpPrimaryAttackAnimation_Implementation(){
}

void AQuintCharacter::BpBlockAnimation_Implementation(){
}

void AQuintCharacter::BpHitAnimation_Implementation(){
}
