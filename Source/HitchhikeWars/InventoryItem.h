#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InventoryItem.generated.h"

UCLASS(Blueprintable)
class HITCHHIKEWARS_API UInventoryItem : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Quantity;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* Icon; // Add icon support
};