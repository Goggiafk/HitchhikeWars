// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "NewLocationTrigger.generated.h"

/**
 * 
 */
UCLASS()
class HITCHHIKEWARS_API ANewLocationTrigger : public ATriggerBox
{
	GENERATED_BODY()

public:
	ANewLocationTrigger();

protected:
	UFUNCTION()
		void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	// Function called when other actors end overlapping with this TriggerBox
	UFUNCTION()
		void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);

};
