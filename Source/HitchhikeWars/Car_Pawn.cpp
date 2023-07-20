// Fill out your copyright notice in the Description page of Project Settings.


#include "Car_Pawn.h"

// Sets default values
ACar_Pawn::ACar_Pawn()
{
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	position = GetActorLocation();
}

// Called when the game starts or when spawned
void ACar_Pawn::BeginPlay()
{
	Super::BeginPlay();
	if(SkeletalMeshComponent)
		SkeletalMeshComponent->SetSkeletalMesh(car_meshes[FMath::RandRange(0, car_meshes.Num()-1)]);
}

void ACar_Pawn::SetPosition(FVector p)
{
	position = p;
}

// Called every frame
void ACar_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	position.Set(position.X + speed, position.Y, position.Z);
	SetActorLocation(position);
}

// Called to bind functionality to input
void ACar_Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

