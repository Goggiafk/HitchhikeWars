// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	// Widget Classes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UUserWidget> InGameMenuWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UUserWidget> MapWidgetClass;

	// Widget Instances
	UPROPERTY()
	UUserWidget* InGameMenuWidget;

	UPROPERTY()
	UUserWidget* MapWidget;

	// Widget States
	UPROPERTY()
	bool IsMenuOpen = false;

	UPROPERTY()
	bool IsMapOpen = false;

	// Input Actions
	void ToggleInGameMenu();
	void ToggleInGameMap();

	// Toggle Widget Function
	UFUNCTION(BlueprintCallable, Category = "Widgets")
	void ToggleWidget(UUserWidget*& Widget, TSubclassOf<UUserWidget> WidgetClass, bool& bIsOpen);
};
