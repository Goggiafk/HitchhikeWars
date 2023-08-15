// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AdvancedFriendsGameInstance.h"
#include "CustomGameInstance.h"
#include "InventoryComponent.h"
#include "InventoryWidget.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "MyGamePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class HITCHHIKEWARS_API AMyGamePlayerController : public APlayerController
{
	GENERATED_BODY()

 public:
	AMyGamePlayerController();

	UInventoryComponent* InventoryComponent;
	
	//items
	UPROPERTY(EditAnywhere, Category = "Starter Items")
	TSoftObjectPtr<UInventoryItem> Rifle;
	
	UPROPERTY(EditAnywhere, Category = "Starter Items")
	TSoftObjectPtr<UInventoryItem> Bullets;
	

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	// Widget Classes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UUserWidget> InGameMenuWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UUserWidget> MapWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UUserWidget> InventoryWidgetClass;
	

	// Widget Instances
	UPROPERTY()
	UUserWidget* InGameMenuWidget;

	UPROPERTY()
	UUserWidget* MapWidget;

	UPROPERTY()
	UUserWidget* InventoryWidget;

	// Widget States
	UPROPERTY()
	bool IsMenuOpen = false;

	UPROPERTY()
	bool IsMapOpen = false;

	UPROPERTY()
	bool IsInventoryOpen = false;

	UPROPERTY(BlueprintReadWrite)
	bool IsAnyWidgetOpen = false;
	
	// Input Actions
	void ToggleInGameMenu();
	void ToggleInGameMap();
	void ToggleInGameInventory();

	// Toggle Widget Function
	UFUNCTION(BlueprintCallable, Category = "Widgets")
	void ToggleWidget(UUserWidget*& Widget, TSubclassOf<UUserWidget> WidgetClass, bool& bIsOpen);
};
