// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryComponent.h"
#include "Engine/GameInstance.h"
#include "CustomGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class HITCHHIKEWARS_API UCustomGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UInventoryComponent* SharedInventoryComponent;
	virtual void Init() override;
};
