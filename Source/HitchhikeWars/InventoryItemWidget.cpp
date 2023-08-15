#include "InventoryItemWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Engine/Texture2D.h"

void UInventoryItemWidget::SetInventoryItem(UInventoryItem* Item)
{
	if (Item)
	{
		NameText = Cast<UTextBlock>(GetWidgetFromName("NameText"));
		QuantityText = Cast<UTextBlock>(GetWidgetFromName("QuantityText"));
		IconImage = Cast<UImage>(GetWidgetFromName("IconImage"));
		
		InventoryItem = Item;
		if (IconImage && Item->Icon)
		{
			IconImage->SetBrushFromTexture(Item->Icon);
		}
		if (NameText)
		{
			NameText->SetText(FText::FromString(Item->Name));
		}
		if (QuantityText)
		{
			QuantityText->SetText(FText::AsNumber(Item->Quantity));
		}
	}
}