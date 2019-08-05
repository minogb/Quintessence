// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Avatar.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetReplicates(true);
	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileComponent->ProjectileGravityScale = 0;
	ProjectileComponent->MaxSpeed = MaxSpeed;
	ProjectileCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Hit Box"));
	ProjectileComponent->SetIsReplicated(true);
	if (ProjectileCollision) {
		ProjectileCollision->InitSphereRadius(CollisionSize);
		ProjectileCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
		ProjectileCollision->SetCollisionResponseToChannel(ECC_ProjectileBlock, ECollisionResponse::ECR_Ignore);
		ProjectileCollision->SetVisibility(true);
		ProjectileCollision->bHiddenInGame = false;
		ProjectileCollision->SetCanEverAffectNavigation(false);
		ProjectileCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		ProjectileCollision->OnComponentBeginOverlap.AddDynamic(this, &AProjectileBase::ProjectileCollided);
		
		SetRootComponent(ProjectileCollision);
	}
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(Target)) {
		ProjectileComponent->HomingTargetComponent = Target->GetRootComponent();
		ProjectileComponent->bIsHomingProjectile = true;
		ProjectileComponent->HomingAccelerationMagnitude = AccelerationSpeed;
	}
	else {
		Destroy(true);
	}
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectileBase::ProjectileCollided(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp,
											int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult){
	ECollisionResponse  response = OtherComp->GetCollisionResponseToChannel(ECC_ProjectileBlock);
	//Is the collision valid
	if (!HasAuthority() || OtherActor == GetInstigator() || OtherActor == GetOwner())
		return;
	//Collided with our target
	else if (OtherActor == Target)
		ProjectileCollidedWithTarget(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	//Note any static meseh actor or otherwise needs to have genearte overlap events on for this to work
	else if(response == ECollisionResponse::ECR_Block || response == ECollisionResponse::ECR_Overlap)
		ProjectileCollidedWithBlocking(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AProjectileBase::ProjectileCollidedWithTarget(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, 
											int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult){
	//By default we apply our damage to the other actor
	if (IsValid(OtherActor) && OtherActor->GetClass()->ImplementsInterface(UInteractable::StaticClass())) {

		IInteractable::Execute_ApplyDamage(OtherActor,DamageStructure,GetInstigator(),(AController*)GetOwner());
	}
	Destroy(true);
}

void AProjectileBase::ProjectileCollidedWithBlocking(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, 
											int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult){
	Destroy(true);
}

