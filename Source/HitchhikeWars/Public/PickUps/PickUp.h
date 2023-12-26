// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "PickUp.generated.h"

UENUM(BlueprintType)
enum class ResourceType : uint8
{
	None,
	Fuel,
	Scrap,
};

UCLASS()
class HITCHHIKEWARS_API APickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUp();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ResourceType CurrentType;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere)
	TArray<UStaticMesh*> Meshes;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
