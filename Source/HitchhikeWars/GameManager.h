// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#pragma warning(push)
#pragma warning(disable: 4996)
#include "SteamAchievementManager.h"
#pragma warning(pop)
#include "InventoryComponent.h"
#include "GameFramework/Actor.h"
#include "GameManager.generated.h"

UCLASS()
class HITCHHIKEWARS_API AGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameManager();
	static AGameManager* GetInstance();

	// Access to SteamAchievementManager functionality
	UPROPERTY()
	USteamAchievementManager* SteamAchievementManager;
	UPROPERTY()
	UInventoryComponent* InventoryComponent;

	void InitializeSteamAchievementManager();
	void InitializeInventoryComponent();
};
