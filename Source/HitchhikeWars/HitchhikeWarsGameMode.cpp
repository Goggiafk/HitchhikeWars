// Copyright Epic Games, Inc. All Rights Reserved.

#include "HitchhikeWarsGameMode.h"
#include "HitchhikeWarsCharacter.h"
#include "UObject/ConstructorHelpers.h"

AHitchhikeWarsGameMode::AHitchhikeWarsGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	PrimaryActorTick.bCanEverTick = true;
}

void AHitchhikeWarsGameMode::BeginPlay()
{
	Super::BeginPlay();
	SpawnCar();
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(UnusedHandle, this, &AHitchhikeWarsGameMode::SpawnCar, FMath::RandRange(2, 5), true);
}

void AHitchhikeWarsGameMode::StartPlay()
{
	Super::StartPlay();
}

void AHitchhikeWarsGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AHitchhikeWarsGameMode::SpawnCar()
{
	float RandX = FMath::RandRange(Spawn_X_Min, Spawn_X_Max);
	float RandY = FMath::RandRange(Spawn_Y_Min, Spawn_Y_Max);

	FVector SpawnPosition = FVector(RandX, RandY, Spawn_Z);
	FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);
	
	GetWorld()->SpawnActor(CarPrefab, &SpawnPosition, &SpawnRotation);
}
