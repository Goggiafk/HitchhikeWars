// Fill out your copyright notice in the Description page of Project Settings.


#include "Gamemanager.h"
#include "EngineUtils.h"


AGameManager::AGameManager()
{
	// Set this actor to call Tick() every frame
	PrimaryActorTick.bCanEverTick = false;
}

AGameManager* AGameManager::GetInstance()
{
	UWorld* World = GEngine->GetWorldFromContextObject(nullptr, EGetWorldErrorMode::LogAndReturnNull);
	if (IsValid(World))
	{
		for (TActorIterator<AGameManager> It(World); It; ++It)
		{
			return *It;
		}
	}

	return nullptr;
}

void AGameManager::InitializeSteamAchievementManager()
{
	SteamAchievementManager = NewObject<USteamAchievementManager>(this);
}

void AGameManager::InitializeInventoryComponent()
{
	InventoryComponent = NewObject<UInventoryComponent>(this);
}

