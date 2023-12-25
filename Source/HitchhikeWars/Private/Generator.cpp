// Fill out your copyright notice in the Description page of Project Settings.


#include "Generator.h"

#include "Components/BoxComponent.h"
#include "HitchhikeWars/TP_ThirdPerson/TP_ThirdPersonCharacter.h"

// Sets default values
AGenerator::AGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetBoxExtent(FVector(100, 100, 100));
	RootComponent = CollisionComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(CollisionComponent);

}

void AGenerator::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if(OtherActor->IsA(ATP_ThirdPersonCharacter::StaticClass()))
	{
		ATP_ThirdPersonCharacter* ThirdPerson = Cast<ATP_ThirdPersonCharacter>(OtherActor);

		ThirdPerson->Carry(false);
	}
}

// Called when the game starts or when spawned
void AGenerator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

