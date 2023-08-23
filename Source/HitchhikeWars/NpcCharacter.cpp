// Fill out your copyright notice in the Description page of Project Settings.


#include "NpcCharacter.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "NPCAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "TP_ThirdPerson/TP_ThirdPersonCharacter.h"

// Sets default values
ANpcCharacter::ANpcCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(34.0f, 80.0f);
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
}

// Called when the game starts or when spawned
void ANpcCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ANpcCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANpcCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

