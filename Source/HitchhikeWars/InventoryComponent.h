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

	UFUNCTION(BlueprintCallable)
	bool AddItem(UInventoryItem* ItemToAdd);

	UFUNCTION(BlueprintCallable)
	bool RemoveItem(UInventoryItem* ItemToRemove);

	UFUNCTION(BlueprintCallable)
	TArray<UInventoryItem*> GetInventoryItems() const;

private:
	UPROPERTY()
	TArray<UInventoryItem*> InventoryItems;
};