// Fill out your copyright notice in the Description page of Project Settings.


#include "NewLocationTrigger.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ShapeComponent.h"

ANewLocationTrigger::ANewLocationTrigger()
{
	// Bind overlap events
	OnActorBeginOverlap.AddDynamic(this, &ANewLocationTrigger::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &ANewLocationTrigger::OnOverlapEnd);
}

void ANewLocationTrigger::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	UGameplayStatics::OpenLevel(this, TEXT("Demonstration"));
}

void ANewLocationTrigger::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	// Handle the functionality when other actors end overlapping with this TriggerBox
	// For example, you can call a function, reset a bool variable, or perform other actions.
}

