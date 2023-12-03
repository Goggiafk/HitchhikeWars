// Fill out your copyright notice in the Description page of Project Settings.


#include "HudWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UHudWidget::UpdateHealthUI(int health)
{
	HealthText = Cast<UTextBlock>(GetWidgetFromName("HealthText"));
	HealthBar = Cast<UProgressBar>(GetWidgetFromName("HealthBar"));

	if(HealthText)
	{
		HealthText->SetText(FText::FromString(FString::FromInt(health)));
	}
	
	if(HealthBar)
	{
		float NormalizedHealth = FMath::Clamp(static_cast<float>(health)/100, 0.0f, 1.0f);
		HealthBar->SetPercent(NormalizedHealth);
		if(health <= 0)
		{
			HealthBar->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UHudWidget::UpdateSleepUI(int SleepPoints)
{
	SleepText = Cast<UTextBlock>(GetWidgetFromName("SleepText"));
	SleepBar = Cast<UProgressBar>(GetWidgetFromName("SleepBar"));

	if(SleepText)
	{
		SleepText->SetText(FText::FromString(FString::FromInt(SleepPoints)));
	}

	if(SleepBar)
	{
		float NormalizedSleep = FMath::Clamp(static_cast<float>(SleepPoints)/100, 0.0f, 1.0f);
		SleepBar->SetPercent(NormalizedSleep);
		if(SleepPoints <= 0)
		{
			SleepBar->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}
