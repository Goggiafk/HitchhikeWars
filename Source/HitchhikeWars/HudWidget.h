// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HudWidget.generated.h"

/**
 * 
 */
UCLASS()
class HITCHHIKEWARS_API UHudWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void UpdateHealthUI(int health);
	void UpdateSleepUI(int SleepPoints);
private:
	int Count = 0;
	class UTextBlock* HealthText;
	class UProgressBar* HealthBar;
	class UTextBlock* SleepText;
	class UProgressBar* SleepBar;
};
