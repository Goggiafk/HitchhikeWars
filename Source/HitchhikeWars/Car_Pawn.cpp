// Fill out your copyright notice in the Description page of Project Settings.


#include "Car_Pawn.h"

// Sets default values
ACar_Pawn::ACar_Pawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	position = GetActorLocation();
}

// Called when the game starts or when spawned
void ACar_Pawn::BeginPlay()
{
	Super::BeginPlay();
		
}

// Called every frame
void ACar_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	position.Set(position.X + 6, position.Y, position.Z);
	SetActorLocation(position);
}

// Called to bind functionality to input
void ACar_Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

