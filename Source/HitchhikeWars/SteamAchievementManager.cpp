// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamAchievementManager.h"

#include "Steam/steam_api.h"

void USteamAchievementManager::InitSteamAPI()
{
	if (!SteamAPI_Init())
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to initialize Steam API"));
	}
}

void USteamAchievementManager::UnlockAchievement(const FString& AchievementName)
{
	if (SteamUserStats())
	{
		SteamUserStats()->SetAchievement(TCHAR_TO_UTF8(*AchievementName));
		SteamUserStats()->StoreStats();
	}
}

void USteamAchievementManager::RemoveAchievement(const FString& AchievementName)
{
	if (SteamUserStats())
	{
		SteamUserStats()->ClearAchievement(TCHAR_TO_UTF8(*AchievementName));
		SteamUserStats()->StoreStats();
	}
}

bool USteamAchievementManager::IsAchievementUnlocked(const FString& AchievementName)
{
	bool bAchievementUnlocked = false;

	if (SteamUserStats())
	{
		SteamUserStats()->GetAchievement(TCHAR_TO_UTF8(*AchievementName), &bAchievementUnlocked);
	}

	return bAchievementUnlocked;
}

void USteamAchievementManager::ShutdownSteamAPI()
{
	if (SteamAPI_IsSteamRunning())
	{
		SteamAPI_Shutdown();
	}
}