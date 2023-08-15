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
	UFUNCTION(BlueprintCallable)
	void SetInventoryItem(UInventoryItem* Item);
	
private:
	class UTextBlock* NameText;
	class UTextBlock* QuantityText;
	class UImage* IconImage;

	UPROPERTY()
	UInventoryItem* InventoryItem;
};