// Fill out your copyright notice in the Description page of Project Settings.


#include "Generator.h"

#include "Components/BoxComponent.h"
#include "Components/ProgressBar.h"
#include "Components/WidgetComponent.h"
#include "HitchhikeWars/TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "Logging/LogMacros.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AGenerator::AGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetBoxExtent(FVector(100, 100, 100));
	RootComponent = CollisionComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(CollisionComponent);

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetWidgetSpace(EWidgetSpace::World);
	WidgetComponent->SetupAttachment(MeshComponent);

	// Set default values
	InitialProgressBarValue = 1.0f;
	CurrentProgressBarValue = 1.0f;
}

void AGenerator::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if(OtherActor->IsA(ATP_ThirdPersonCharacter::StaticClass()))
	{
		ATP_ThirdPersonCharacter* ThirdPerson = Cast<ATP_ThirdPersonCharacter>(OtherActor);

		if(ThirdPerson->HeldResource == ResourceType::Fuel)
		{
			AddToProgressBar(0.1f);
			ThirdPerson->Carry(false);
			return;
		}
	}
}

void AGenerator::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate the CurrentProgressBarValue property
	DOREPLIFETIME(AGenerator, CurrentProgressBarValue);
}

// Called when the game starts or when spawned
void AGenerator::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* WidgetInstance = Cast<UUserWidget>(WidgetComponent->GetUserWidgetObject());
	if(WidgetComponent)
	{
		UProgressBar* ProgressBar = Cast<UProgressBar>(WidgetInstance->GetWidgetFromName(TEXT("ProgressBar")));
		if (ProgressBar)
		{
			ProgressBar->SetPercent(InitialProgressBarValue);
		}

		// Start decreasing the progress bar over time
		GetWorldTimerManager().SetTimer(
			TimerHandle_DecreaseProgressBar,
			this,
			&AGenerator::DecreaseProgressBar,
			1.0f,
			true
			);
	}
}

// Called every frame
void AGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGenerator::DecreaseProgressBar()
{
	// Decrease the progress bar value each second
	CurrentProgressBarValue -= DecreaseValue; // You can adjust the rate of decrease

	
	if (CurrentProgressBarValue <= 0.0f)
	{
		CurrentProgressBarValue = 0.0f;
		// Optionally, stop the timer or perform additional actions when the progress bar reaches zero.
	}

	// Update the widget's progress bar
	UUserWidget* WidgetInstance = Cast<UUserWidget>(WidgetComponent->GetUserWidgetObject());
	if (WidgetInstance)
	{
		UProgressBar* ProgressBar = Cast<UProgressBar>(WidgetInstance->GetWidgetFromName(TEXT("ProgressBar")));
		if (ProgressBar)
		{
			ProgressBar->SetPercent(CurrentProgressBarValue);
		}
	}

	MulticastAddToProgressBar(CurrentProgressBarValue);
}

void AGenerator::AddToProgressBar(float ValueToAdd)
{
	// Add the specified value to the progress bar
	CurrentProgressBarValue += ValueToAdd;
	if (CurrentProgressBarValue > 1.0f)
	{
		CurrentProgressBarValue = 1.0f; // Cap the progress bar value at 1.0
	}

	// Update the widget's progress bar
	UUserWidget* WidgetInstance = Cast<UUserWidget>(WidgetComponent->GetUserWidgetObject());
	if (WidgetInstance)
	{
		UProgressBar* ProgressBar = Cast<UProgressBar>(WidgetInstance->GetWidgetFromName(TEXT("ProgressBar")));
		if (ProgressBar)
		{
			ProgressBar->SetPercent(CurrentProgressBarValue);
		}
	}

	MulticastAddToProgressBar(CurrentProgressBarValue);
}

void AGenerator::MulticastAddToProgressBar_Implementation(float ValueToAdd)
{
	UUserWidget* WidgetInstance = Cast<UUserWidget>(WidgetComponent->GetUserWidgetObject());
	if (WidgetInstance)
	{
		UProgressBar* ProgressBar = Cast<UProgressBar>(WidgetInstance->GetWidgetFromName(TEXT("ProgressBar")));
		if (ProgressBar)
		{
			ProgressBar->SetPercent(CurrentProgressBarValue);
		}
	}
}

bool AGenerator::MulticastAddToProgressBar_Validate(float ValueToAdd)
{
	// This is the validation function for the MulticastAddToProgressBar function.
	// You can implement additional checks here if needed.
	return false;
}

