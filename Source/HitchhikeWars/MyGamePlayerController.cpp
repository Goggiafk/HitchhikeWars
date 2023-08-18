// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGamePlayerController.h"

#include "GameManager.h"
#include "InventoryComponent.h"
#include "InventoryItem.h"
#include "InventoryWidget.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Steam/steam_api.h"
#include "TP_ThirdPerson/TP_ThirdPersonCharacter.h"

AMyGamePlayerController::AMyGamePlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
}

void AMyGamePlayerController::BeginPlay()
{
 	Super::BeginPlay();

	// if(SteamAPI_Init())
	// {
	// 	MyId = SteamUser()->GetSteamID();
	// }
	//
	// AGameManager* GameManager = AGameManager::GetInstance();
	// if (GameManager)
	// {
	// 	GameManager->InitializeSteamAchievementManager();
	//
	// 	if (GameManager->SteamAchievementManager)
	// 	{
	// 		GameManager->SteamAchievementManager->InitSteamAPI();
	// 		GameManager->SteamAchievementManager->UnlockAchievement(TEXT("LogIn_1"));
	// 		//bool bUnlocked = GameManager->SteamAchievementManager->IsAchievementUnlocked(TEXT("LogIn_1"));
	// 		//GameManager->SteamAchievementManager->ShutdownSteamAPI();
	// 	}
	// }
	
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

void AMyGamePlayerController::ToggleInventory(bool DetectIfOpen)
{
	//ToggleInGameInventory();
	bShowMouseCursor = false;
	InventoryWidget->RemoveFromParent();
}


void AMyGamePlayerController::ToggleInGameInventory()
{
	if(InventoryWidgetClass && !IsAnyWidgetOpen && InventoryComponent)
	{
		//UInventoryItem* TestItem = NewObject<UInventoryItem>();
		// TestItem->Name = "Sex";
		// TestItem->Quantity = 1;
		// InventoryComponent->AddItem(TestItem);
		TArray<UInventoryItem*> InventoryItems = Cast<ATP_ThirdPersonCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->InventoryComponent->GetInventoryItems(); // Assuming you have a function to get inventory items

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