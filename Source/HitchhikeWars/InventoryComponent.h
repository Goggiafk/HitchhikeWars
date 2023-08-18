#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryItem.h"
#include "InventoryComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HITCHHIKEWARS_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();
	
	bool AddItem(UInventoryItem* ItemToAdd);
	
	bool RemoveItem(UInventoryItem* ItemToRemove);

	bool DecreaseItemByType(EItemType Type);

	UInventoryItem* GetItemByType(EItemType Type);

	bool IfItemExists(EItemType Type);

	UFUNCTION(BlueprintCallable)
	TArray<UInventoryItem*> GetInventoryItems() const;

private:
	UPROPERTY()
	TArray<UInventoryItem*> InventoryItems;
};