// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SteamAchievementManager.generated.h"

/**
 * 
 */
UCLASS()
class HITCHHIKEWARS_API USteamAchievementManager : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Steam Achievements")
	static void InitSteamAPI();

	UFUNCTION(BlueprintCallable, Category = "Steam Achievements")
	static void UnlockAchievement(const FString& AchievementName);

	UFUNCTION(BlueprintCallable, Category = "Steam Achievements")
	void RemoveAchievement(const FString& AchievementName);

	UFUNCTION(BlueprintCallable, Category = "Steam Achievements")
	static bool IsAchievementUnlocked(const FString& AchievementName);

	UFUNCTION(BlueprintCallable, Category = "Steam Achievements")
	static void ShutdownSteamAPI();
};