// Copyright Epic Games, Inc. All Rights Reserved.

#include "HitchhikeWarsGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "Car_Pawn.h"
#include "Net/UnrealNetwork.h"

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
	GetWorldTimerManager().SetTimer(UnusedHandle, this, &AHitchhikeWarsGameMode::SpawnCar, FMath::RandRange(3, spawnDelay), true);
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
	if(HasAuthority())
	{
		SpawnCar_Multicast();
	}
}

void AHitchhikeWarsGameMode::SpawnCar_Multicast_Implementation()
{
	float RandX = -4000;//FMath::RandRange(Spawn_X_Min, Spawn_X_Max);
	float RandY = -550;//FMath::RandRange(Spawn_Y_Min, Spawn_Y_Max);

	SpawnPosition = FVector(RandX, RandY, Spawn_Z);
	SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);
	
	OnRep_SpawnCar();
}

void AHitchhikeWarsGameMode::OnRep_SpawnCar()
{
	FActorSpawnParameters SpawnParameter;
	SpawnParameter.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	ACar_Pawn* car = GetWorld()->SpawnActor<ACar_Pawn>(CarPrefab, SpawnPosition, SpawnRotation, SpawnParameter);
	if(car)
	{
		car->SetUpPosition_Multicast(SpawnPosition);
	}
}

void AHitchhikeWarsGameMode::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AHitchhikeWarsGameMode, SpawnPosition);
	DOREPLIFETIME(AHitchhikeWarsGameMode, SpawnRotation);
}
