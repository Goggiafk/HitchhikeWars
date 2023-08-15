#include "InventoryWidget.h"
#include "InventoryItemWidget.h" // Create this widget to display individual items
#include "Components/VerticalBox.h"

void UInventoryWidget::SetInventoryItems(const TArray<UInventoryItem*>& Items)
{
    CreateInventoryItemWidgets(Items);
}

void UInventoryWidget::CreateInventoryItemWidgets(const TArray<UInventoryItem*>& Items)
{
    ItemContainer = Cast<UVerticalBox>(GetWidgetFromName("ItemContainer"));
    if (InventoryItemWidgetClass && ItemContainer)
    {
        ItemContainer->ClearChildren();

        for (UInventoryItem* Item : Items)
        {
            UInventoryItemWidget* ItemWidget = CreateWidget<UInventoryItemWidget>(this, InventoryItemWidgetClass);
            if (ItemWidget)
            {
                ItemWidget->SetInventoryItem(Item);
                ItemContainer->AddChild(ItemWidget);
            }
        }
    }
}