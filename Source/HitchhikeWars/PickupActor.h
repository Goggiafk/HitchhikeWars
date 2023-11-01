// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItem.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "PickupActor.generated.h"

UCLASS()
class HITCHHIKEWARS_API APickupActor : public AActor
{
	GENERATED_BODY()
	
public:
	APickupActor();

	UPROPERTY(EditAnywhere, Category = "Item Data")
    EItemType ItemType;
	
	UPROPERTY(EditAnywhere, Category = "Item Data")
	FString ItemName;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	int32 ItemQuantity;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	UTexture2D* ItemIcon;

	UPROPERTY(EditAnywhere, Category = "PickUp Parameter")
	bool IsInfinite;

protected:
	UPROPERTY(VisibleAnywhere)
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere)
	float RotationSpeed = 100;
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

};
