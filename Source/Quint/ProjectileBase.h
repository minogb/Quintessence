// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enumerations.h"
#include "ProjectileBase.generated.h"

UCLASS()
class QUINT_API AProjectileBase : public AActor
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	class UProjectileMovementComponent* ProjectileComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true", ExposeOnSpawn = "true"))
	class USphereComponent* ProjectileCollision;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true", ExposeOnSpawn = "true"))
	float CollisionSize = 32.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true", ExposeOnSpawn = "true"))
	float AccelerationSpeed = 10000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true", ExposeOnSpawn = "true"))
	float MaxSpeed = 1000.f;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true", ExposeOnSpawn = "true"))
	AActor* Target = NULL;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true", ExposeOnSpawn = "true"))
	FDamageStruct DamageStructure;
	// Sets default values for this actor's properties
	AProjectileBase();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void ProjectileCollided(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult &SweepResult);
	virtual void ProjectileCollidedWithTarget(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	virtual void ProjectileCollidedWithBlocking(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);


};
