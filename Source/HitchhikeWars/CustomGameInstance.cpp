// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameInstance.h"

void UCustomGameInstance::Init()
{
	Super::Init();

	SharedInventoryComponent = NewObject<UInventoryComponent>(this);
	// Set up other properties, initialization, etc. for the inventory component
}