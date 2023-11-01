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

void UHudWidget::IncreaseReadyCount(bool authority)
{
	ReadyCount1 = Cast<UTextBlock>(GetWidgetFromName("ReadyCount1"));
	if(authority){
		Count++;
		if(ReadyCount1)
		{
			ReadyCount1->SetText(FText::FromString(FString::FromInt(Count)));
		}
		if(Count == 4)
		{
			ReadyCount1->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	else
	{
		ReadyCount1->SetVisibility(ESlateVisibility::Hidden);
	}
}
