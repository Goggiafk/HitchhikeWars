// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGameMode.h"

#include "GameManager.h"
#include "SteamAchievementManager.h"


AMainMenuGameMode::AMainMenuGameMode()
{
}

void AMainMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	FFileHelper::SaveStringToFile(TEXT(RAW_APP_ID), TEXT("steam_appid.txt"));
	SteamAPI_RestartAppIfNecessary(atoi(APP_ID));

	if(SteamAPI_Init())
	{
		MyId = SteamUser()->GetSteamID();
	}

	AGameManager* GameManager = AGameManager::GetInstance();
	if (GameManager)
	{
		GameManager->InitializeSteamAchievementManager();

		if (GameManager->SteamAchievementManager)
		{
			GameManager->SteamAchievementManager->InitSteamAPI();
			GameManager->SteamAchievementManager->RemoveAchievement(TEXT("LogIn_1"));
			GameManager->SteamAchievementManager->UnlockAchievement(TEXT("LogIn_1"));
			//bool bUnlocked = GameManager->SteamAchievementManager->IsAchievementUnlocked(TEXT("LogIn_1"));
			//GameManager->SteamAchievementManager->ShutdownSteamAPI();
		}
	}

}
