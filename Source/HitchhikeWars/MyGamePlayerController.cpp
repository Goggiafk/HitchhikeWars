// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGamePlayerController.h"

#include "Blueprint/UserWidget.h"

AMyGamePlayerController::AMyGamePlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMyGamePlayerController::BeginPlay()
{
 	Super::BeginPlay();
     
 	// Load and store the widget class in the constructor or BeginPlay
 	//InGameMenuWidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("WidgetClassPath"));
	SetInputMode(FInputModeGameAndUI());
 }

void AMyGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("ToggleInGameMenu", IE_Pressed, this, &AMyGamePlayerController::ToggleInGameMenu);
	InputComponent->BindAction("ToggleInGameMap", IE_Pressed, this, &AMyGamePlayerController::ToggleInGameMap);
}

void AMyGamePlayerController::ToggleInGameMenu()
{
	if (InGameMenuWidgetClass && !IsMapOpen)
	{
		ToggleWidget(InGameMenuWidget, InGameMenuWidgetClass, IsMenuOpen);
	}
}

void AMyGamePlayerController::ToggleInGameMap()
{
	if (MapWidgetClass && !IsMenuOpen)
	{
		ToggleWidget(MapWidget, MapWidgetClass, IsMapOpen);
	}
}

void AMyGamePlayerController::ToggleWidget(UUserWidget*& Widget, TSubclassOf<UUserWidget> WidgetClass, bool& bIsOpen)
{
	if (!Widget)
	{
		Widget = CreateWidget<UUserWidget>(this, WidgetClass);
	}

	if (Widget)
	{
		if (bIsOpen)
		{
			bShowMouseCursor = false;
			Widget->RemoveFromParent();
		}
		else
		{
			bShowMouseCursor = true;
			Widget->AddToViewport();
		}

		bIsOpen = !bIsOpen;
	}
}