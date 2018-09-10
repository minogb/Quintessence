// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "BaseDoor.generated.h"

UCLASS()
class QUINT_API ABaseDoor : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Audio")
	class USoundBase* OpenSound;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Audio")
	class USoundBase* CloseSound;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Visual")
	class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Visual")
	class UBoxComponent* HitBox;

	UPROPERTY(ReplicatedUsing=OnRepOpen)
	bool IsOpen =false;

public:
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnRepOpen();
public:
	// Sets default values for this actor's properties
	ABaseDoor();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE bool IsDoorOpen() { return IsOpen; }

	virtual EInteractionType GetDefaultTask() override { return Use; }
	virtual int32 GetAvaliableTasks() override { return Use | Move_Here; }
	virtual void UseObject() { if (HasAuthority())IsOpen = !IsOpen; OnRepOpen(); }
};
