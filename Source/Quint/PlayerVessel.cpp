// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerVessel.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/World.h"
#include "Engine/GameEngine.h"

// Sets default values
APlayerVessel::APlayerVessel()
{
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	// Don't want arm to rotate when character does
	CameraBoom->bAbsoluteRotation = false; 
	 // Don't want to pull camera in when it collides with level
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 2500.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	
	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->RelativeRotation = FRotator(0,0,-180.f);
	// Camera does not rotate relative to arm
	TopDownCameraComponent->bUsePawnControlRotation = false; 

	PlayerAvatar = nullptr;
}

// Called to bind functionality to input
void APlayerVessel::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("PanMode", IE_Pressed, this, &APlayerVessel::PressPan);
	PlayerInputComponent->BindAction("PanMode", IE_Released, this, &APlayerVessel::ReleasePan);

	PlayerInputComponent->BindAxis("MouseUp", this, &APlayerVessel::MoveMouseY);
	PlayerInputComponent->BindAxis("MouseRight", this, &APlayerVessel::MoveMouseX);

}
// Called when the game starts or when spawned
void APlayerVessel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerVessel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AttachToAvatar();
}
void APlayerVessel::AttachToAvatar(){
	if(PlayerAvatar && PlayerAvatar->IsValidLowLevel()){
		if(!this->IsAttachedTo(PlayerAvatar)){
			this->AttachToActor(PlayerAvatar, FAttachmentTransformRules::KeepRelativeTransform);
		}
	}
}


void APlayerVessel::ReleasePan(){
	SetPanning(false);
}
void APlayerVessel::PressPan(){
	SetPanning(true);
}

void APlayerVessel::SetPanning(bool Panning){
	APlayerController* pc = Cast<APlayerController>(GetController());
	if(pc){
		pc->bShowMouseCursor=!Panning;
		IsPanning = Panning;
		if(Panning){
			float x=0;
			float y=0;
			pc->GetMousePosition(x,y);
			LockedMousePos.Set(x,y);
		}
		else{
		}
	}
}

void APlayerVessel::MoveMouseX(float Val){
	if(IsPanning){
		AddControllerYawInput(Val*(20*10) * GetWorld()->GetDeltaSeconds());
		APlayerController* pc =  Cast<APlayerController>(GetController());
		if(pc){
			pc->SetMouseLocation(LockedMousePos.X,LockedMousePos.Y);
		}
	}

}

void APlayerVessel::MoveMouseY(float Val){
	
	if(IsPanning){
		FRotator current = CameraBoom->RelativeRotation;
		float pitch = FMath::ClampAngle((current.Pitch+Val*(PanRotationSpeed) * GetWorld()->GetDeltaSeconds()),-89.f,0.f);
		current.Pitch = pitch;
		CameraBoom->SetRelativeRotation(current);

	}
}