// Fill out your copyright notice in the Description page of Project Settings.


#include "NpcCharacter.h"

#include "AIController.h"
#include "Car_Pawn.h"
#include "NavigationSystem.h"
#include "NPCAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "Perception/PawnSensingComponent.h"
#include "TP_ThirdPerson/TP_ThirdPersonCharacter.h"

// Sets default values
ANpcCharacter::ANpcCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(34.0f, 80.0f);
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
	PawnSensingComponent->OnSeePawn.AddDynamic(this, &ANpcCharacter::SeesPlayer);
	RetriggerableTimerDelegate.BindUFunction(this, FName("ResetHasSeenPlayer"));

	CurrentHealth = MaxHealth;
}

// Called when the game starts or when spawned
void ANpcCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ANpcCharacter::SeesPlayer(APawn* SeenPlayer)
{
	if (SeenPlayer->IsA(ATP_ThirdPersonCharacter::StaticClass()))
	{
		ATP_ThirdPersonCharacter* PlayerCharacter = Cast<ATP_ThirdPersonCharacter>(SeenPlayer);
		if (PlayerCharacter)
		{
			ChasedPlayer = PlayerCharacter;
			SetHasSeenPlayer(true);
		}
		float DelayInSeconds = 3.0f; // 3 seconds delay
		GetWorldTimerManager().SetTimer(RetriggerableTimerHandle, RetriggerableTimerDelegate, DelayInSeconds, false);

	}
}

void ANpcCharacter::ResetHasSeenPlayer()
{
	SetHasSeenPlayer(false);
}

void ANpcCharacter::SetHasSeenPlayer(bool state)
{
	ANPCAIController* AIController = Cast<ANPCAIController>(GetController());
	if (AIController)
	{
		UBlackboardComponent* BlackboardComp = AIController->FindComponentByClass<UBlackboardComponent>();
		if (BlackboardComp)
		{
			FName KeyName = FName("HasSeenPlayer");
			BlackboardComp->SetValueAsBool(KeyName, state);
		}
	}
}

// Called every frame
void ANpcCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANpcCharacter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
		
	if (OtherActor && OtherActor->IsA(ACar_Pawn::StaticClass()))
	{
		ACar_Pawn* Car = Cast<ACar_Pawn>(OtherActor);
		
		if(Car)
		{
			TakeHealthDamage(150);
		}
	}
	//OtherActor->Destroy();
}

void ANpcCharacter::TakeHealthDamage(float DamageAmount)
{
	if (!bIsDead)
	{
		CurrentHealth -= DamageAmount;
		if (CurrentHealth <= 0)
		{
			bIsDead = true;
			OnDeath();
		}
	}
}

void ANpcCharacter::OnDeath()
{
	GetMesh()->SetSimulatePhysics(true);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AController* AIController = Cast<AController>(GetController());
	//FNavigationSystem::StopMovement(*AIController);
}

void ANpcCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ANpcCharacter, CurrentHealth);
}

