// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#pragma warning(push)
#pragma warning(disable: 4996)
#include "Steam/steam_api.h"
#pragma warning(pop)

#include "MainMenuGameMode.generated.h"

#define RAW_APP_ID "2447630"

UCLASS()
class HITCHHIKEWARS_API AMainMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()
	AMainMenuGameMode();
	virtual void BeginPlay() override;
	
	static constexpr char* APP_ID = RAW_APP_ID;
	CSteamID MyId;
};
