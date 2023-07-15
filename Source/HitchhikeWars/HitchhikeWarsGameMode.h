// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Car_Pawn.h"
#include "GameFramework/GameModeBase.h"
#include "HitchhikeWarsGameMode.generated.h"

UCLASS(minimalapi)
class AHitchhikeWarsGameMode : public AGameModeBase
{
	GENERATED_BODY()
	AHitchhikeWarsGameMode();
	virtual void BeginPlay() override;
	virtual void StartPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<APawn> CarPrefab;

	float Spawn_Z = 0.0f;
	
	UPROPERTY(EditAnywhere)
	float Spawn_X_Min;

	UPROPERTY(EditAnywhere)
	float Spawn_X_Max;

	UPROPERTY(EditAnywhere)
	float Spawn_Y_Min;

	UPROPERTY(EditAnywhere)
	float Spawn_Y_Max;

	UPROPERTY(EditAnywhere)
	FVector2D DelayRange;

	void SpawnCar();
};



