// Fill out your copyright notice in the Description page of Project Settings.


#include "HudWidget.h"
#include "Components/TextBlock.h"

void UHudWidget::UpdateHealthUI(int health)
{
	HealthText = Cast<UTextBlock>(GetWidgetFromName("HealthText"));

	if(HealthText)
	{
		HealthText->SetText(FText::FromString(FString::FromInt(health)));
	}
}
