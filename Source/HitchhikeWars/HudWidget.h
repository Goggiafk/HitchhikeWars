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
private:
	class UTextBlock* HealthText;
};
