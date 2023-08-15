#pragma once

#include "CoreMinimal.h"
#include "InventoryItem.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

UCLASS()
class HITCHHIKEWARS_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetInventoryItems(const TArray<UInventoryItem*>& Items);

private:
	class UVerticalBox* ItemContainer;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UUserWidget> InventoryItemWidgetClass;

	void CreateInventoryItemWidgets(const TArray<UInventoryItem*>& Items);
};