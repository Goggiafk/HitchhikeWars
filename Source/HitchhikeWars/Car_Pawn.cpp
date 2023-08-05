// Fill out your copyright notice in the Description page of Project Settings.


#include "Car_Pawn.h"

#include "Net/UnrealNetwork.h"

// Sets default values
ACar_Pawn::ACar_Pawn()
{
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//position = GetActorLocation();
	//CurrentCarMesh = SkeletalMeshComponent->GetSkeletalMeshAsset();
}

// Called when the game starts or when spawned
void ACar_Pawn::BeginPlay()
{
	Super::BeginPlay();
	if(HasAuthority())
	{
		SetUpCar_Multicast();
	}
}

// Called every frame
void ACar_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(HasAuthority())
	{
		SetPosition_Multicast();
	}
}


void ACar_Pawn::SetUpCar_Multicast_Implementation()
{
	CurrentCarMesh = car_meshes[FMath::RandRange(0, car_meshes.Num()-1)];
	
	OnRep_SetUpCar();
}

void ACar_Pawn::OnRep_SetUpCar()
{
	if(SkeletalMeshComponent)
	{
		SkeletalMeshComponent->SetSkeletalMesh(CurrentCarMesh);
	}

	Speed = FMath::RandRange(20, 30);
}

void ACar_Pawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACar_Pawn, CurrentCarMesh);
	DOREPLIFETIME(ACar_Pawn, CarPosition);
	DOREPLIFETIME(ACar_Pawn, Speed);
}


void ACar_Pawn::SetPosition_Multicast_Implementation()
{
	CarPosition.Set(CarPosition.X + Speed, CarPosition.Y, CarPosition.Z);

	OnRep_SetPosition();
}

void ACar_Pawn::SetUpPosition_Multicast_Implementation(FVector p)
{
	CarPosition = p;

	OnRep_SetPosition();
}

void ACar_Pawn::OnRep_SetPosition()
{
	SetActorLocation(CarPosition);
	if(CarPosition.X > 6500.0f)
	{
		Destroy();
	}
}

// Called to bind functionality to input
void ACar_Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

