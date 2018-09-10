// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseDoor.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine.h"
#include "UnrealNetwork.h"

void ABaseDoor::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseDoor, IsOpen);
}
// Sets default values
ABaseDoor::ABaseDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetReplicates(true);
	/*
	static ConstructorHelpers::FObjectFinder<USoundBase>OpenSoundObj(TEXT("SoundCue'/Game/CustomSounds/DoorOpenCue.DoorOpenCue'"));
	static ConstructorHelpers::FObjectFinder<USoundBase>CloseSoundObj(TEXT("SoundCue'/Game/CustomSounds/DoorCloseCue.DoorCloseCue'"));
	if (CloseSoundObj.Succeeded())
		CloseSound = CloseSoundObj.Object;
	if (OpenSoundObj.Succeeded())
		OpenSound = OpenSoundObj.Object;
		*/
	//Hitbox Setup
	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Hit Box"));
	HitBox->SetupAttachment(RootComponent);
	HitBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	HitBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	HitBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	HitBox->InitBoxExtent(FVector(5, 45, 100));
	HitBox->SetCanEverAffectNavigation(false);
	//Mesh Setup
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(HitBox);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	HitBox->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	Mesh->SetRelativeLocation(FVector(0, 45, -100));
	Mesh->SetCanEverAffectNavigation(false);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/StarterContent/Props/SM_Door.SM_Door'"));
	if (MeshAsset.Succeeded())
		Mesh->SetStaticMesh(MeshAsset.Object);
}

// Called when the game starts or when spawned
void ABaseDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseDoor::OnRepOpen()
{
	FRotator rotation;
	ECollisionResponse blocking;
	USoundBase* SoundToPlay;
	if (IsOpen) {
		rotation = FRotator(0.f, 90.f, 0.f);
		blocking = ECR_Ignore;
		SoundToPlay = OpenSound;
	}
	else {
		rotation = FRotator(0.f, -90.f, 0.f);
		blocking = ECR_Block;
		SoundToPlay = CloseSound;
	}
	Mesh->AddLocalRotation(rotation);
	HitBox->SetCollisionResponseToChannel(ECC_Pawn, blocking);
	UWorld* world = GetWorld();
	if (world && CloseSound)
		UGameplayStatics::PlaySoundAtLocation(world, CloseSound, GetActorLocation());
}

// Called every frame
void ABaseDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

