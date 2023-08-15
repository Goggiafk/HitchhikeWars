// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGamePlayerController.h"

#include "AdvancedFriendsGameInstance.h"
#include "CustomGameInstance.h"
#include "GameManager.h"
#include "InventoryComponent.h"
#include "InventoryWidget.h"
#include "Blueprint/UserWidget.h"

AMyGamePlayerController::AMyGamePlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
}

void AMyGamePlayerController::BeginPlay()
{
 	Super::BeginPlay();
	if (InventoryComponent)
	{
		//InventoryComponent = CustomGameInstance->SharedInventoryComponent;
		//InventoryComponent = CustomGameInstance->SharedInventoryComponent;
		//UInventoryItem* RifleI = Cast<UInventoryItem>(Rifle.LoadSynchronous());
		//UInventoryItem* BulletsI = Cast<UInventoryItem>(Bullets.LoadSynchronous());
		UInventoryItem* TestItem = NewObject<UInventoryItem>();
		TestItem->Name = "Sex";
		TestItem->Quantity = 1;
		//TestItem->Icon = LoadObject<Tex>();
		
		//InventoryComponent->AddItem(Rifle.LoadSynchronous());
		//InventoryComponent->AddItem(Bullets.LoadSynchronous());
		InventoryComponent->AddItem(TestItem);
	}
	
	SetInputMode(FInputModeGameAndUI());
 }

void AMyGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("ToggleInGameMenu", IE_Pressed, this, &AMyGamePlayerController::ToggleInGameMenu);
	InputComponent->BindAction("ToggleInGameMap", IE_Pressed, this, &AMyGamePlayerController::ToggleInGameMap);
	InputComponent->BindAction("ToggleInGameInventory", IE_Pressed, this, &AMyGamePlayerController::ToggleInGameInventory);
}

void AMyGamePlayerController::ToggleInGameMenu()
{
	if (InGameMenuWidgetClass && !IsAnyWidgetOpen)
	{
		ToggleWidget(InGameMenuWidget, InGameMenuWidgetClass, IsMenuOpen);
	}
}

void AMyGamePlayerController::ToggleInGameMap()
{
	if (MapWidgetClass && !IsAnyWidgetOpen)
	{
		ToggleWidget(MapWidget, MapWidgetClass, IsMapOpen);
	}
}

void AMyGamePlayerController::ToggleInGameInventory()
{
	if(InventoryWidgetClass && !IsAnyWidgetOpen && InventoryComponent)
	{
		//UInventoryItem* TestItem = NewObject<UInventoryItem>();
		// TestItem->Name = "Sex";
		// TestItem->Quantity = 1;
		// InventoryComponent->AddItem(TestItem);
		
		TArray<UInventoryItem*> InventoryItems = InventoryComponent->GetInventoryItems(); // Assuming you have a function to get inventory items
		for (int32 Index = 0; Index < InventoryItems.Num(); ++Index)
		{
			if (InventoryItems[Index])
			{
				FString ItemName = InventoryItems[Index]->Name;
				UE_LOG(LogTemp, Warning, TEXT("Inventory Item at index %d has ItemName: %s"), Index, *ItemName);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Null item at index %d"), Index);
			}
		}
	
		ToggleWidget(InventoryWidget, InventoryWidgetClass, IsInventoryOpen);

		UInventoryWidget* InventoryWidgetInv = Cast<UInventoryWidget>(InventoryWidget);
		InventoryWidgetInv->SetInventoryItems(InventoryItems);
		//FString ItemName = InventoryComponent->GetInventoryItems()[0]->Name;
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