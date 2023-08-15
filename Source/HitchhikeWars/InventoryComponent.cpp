#include "InventoryComponent.h"

UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.
	PrimaryComponentTick.bCanEverTick = false;
}

bool UInventoryComponent::AddItem(UInventoryItem* ItemToAdd)
{
	if (!ItemToAdd)
	{
		return false;
	}

	for (UInventoryItem* InventoryItem : InventoryItems)
	{
		if (InventoryItem->Name == ItemToAdd->Name)
		{
			InventoryItem->Quantity += ItemToAdd->Quantity;
			return true;
		}
	}

	InventoryItems.Add(ItemToAdd);
	return true;
}

bool UInventoryComponent::RemoveItem(UInventoryItem* ItemToRemove)
{
	if (!ItemToRemove)
	{
		return false;
	}

	if (InventoryItems.Contains(ItemToRemove))
	{
		InventoryItems.Remove(ItemToRemove);
		return true;
	}

	return false;
}

TArray<UInventoryItem*> UInventoryComponent::GetInventoryItems() const
{
	return InventoryItems;
}