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
		float percentage = health;
		UE_LOG(LogTemp, Warning, TEXT("prog is %d"), percentage);
		HealthBar->SetPercent(percentage);
	}
}
