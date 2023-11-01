// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupActor.h"

#include "InventoryItem.h"
#include "MyGamePlayerController.h"
#include "GameFramework/GameSession.h"
#include "Kismet/GameplayStatics.h"
#include "TP_ThirdPerson/TP_ThirdPersonCharacter.h"

// Sets default values
APickupActor::APickupActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetSphereRadius(50.0f);
	RootComponent = CollisionComponent;
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetWorldScale3D(FVector(3, 3, 3));
	MeshComponent->SetRelativeScale3D(FVector(3, 3, 3));
	MeshComponent->SetupAttachment(CollisionComponent);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void APickupActor::BeginPlay()
{
	Super::BeginPlay();
}

void APickupActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	FRotator NewRotation = MeshComponent->GetComponentRotation() + FRotator(0.0f, RotationSpeed * DeltaSeconds, 0.0f);
	MeshComponent->SetWorldRotation(NewRotation);
}


