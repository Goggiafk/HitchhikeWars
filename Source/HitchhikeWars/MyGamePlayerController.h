// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryComponent.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"

#pragma warning(push)
#pragma warning(disable: 4996)
#include "Steam/steam_api.h"
#pragma warning(pop)

#include "MyGamePlayerController.generated.h"

#define RAW_APP_ID "2447630"

UCLASS()
class HITCHHIKEWARS_API AMyGamePlayerController : public APlayerController
{
	GENERATED_BODY()

	static constexpr char* APP_ID = RAW_APP_ID;
	CSteamID MyId;
	
 public:
	AMyGamePlayerController();

	UInventoryComponent* InventoryComponent;

	void ToggleInventory(bool DetectIfOpen);

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
