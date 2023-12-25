// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUps/PickUp.h"

#include "HitchhikeWars/TP_ThirdPerson/TP_ThirdPersonCharacter.h"

// Sets default values
APickUp::APickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetBoxExtent(FVector(50, 50, 50));
	RootComponent = CollisionComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(CollisionComponent);
	//MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void APickUp::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickUp::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if(OtherActor->IsA(ATP_ThirdPersonCharacter::StaticClass()))
	{
		ATP_ThirdPersonCharacter* ThirdPerson = Cast<ATP_ThirdPersonCharacter>(OtherActor);

		if(CurrentType == ResourceType::Fuel)
		{
			ThirdPerson->Carry(true);
			Destroy();
		}
		return;
	}
}
