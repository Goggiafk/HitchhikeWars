#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryItem.h"
#include "InventoryItemWidget.generated.h"

UCLASS()
class HITCHHIKEWARS_API UInventoryItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetInventoryItem(UInventoryItem* Item);
	UFUNCTION(BlueprintCallable)
	void OnButtonClicked();
	
private:
	class UButton* ItemButton;
	class UTextBlock* NameText;
	class UTextBlock* QuantityText;
	class UImage* IconImage;
	
	
	UPROPERTY()
	UInventoryItem* InventoryItem;
};