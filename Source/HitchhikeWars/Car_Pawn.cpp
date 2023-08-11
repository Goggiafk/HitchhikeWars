#include "Car_Pawn.h"
#include "Net/UnrealNetwork.h"

ACar_Pawn::ACar_Pawn()
{
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SetRootComponent(SkeletalMeshComponent);
	PrimaryActorTick.bCanEverTick = true;
}

void ACar_Pawn::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority())
	{
		SetUpCar_Multicast();
	}
}

void ACar_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (HasAuthority())
	{
		SetPosition_Multicast();
	}
}

void ACar_Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACar_Pawn::SetUpCar_Multicast_Implementation()
{
	CurrentCarMesh = CarMeshes[FMath::RandRange(0, CarMeshes.Num() - 1)];
	OnRep_SetUpCar();
}

void ACar_Pawn::OnRep_SetUpCar()
{
	if (SkeletalMeshComponent)
	{
		SkeletalMeshComponent->SetSkeletalMesh(CurrentCarMesh);
	}
	Speed = FMath::RandRange(20, 30);
}

void ACar_Pawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ACar_Pawn, CurrentCarMesh);
	DOREPLIFETIME(ACar_Pawn, Position);
	DOREPLIFETIME(ACar_Pawn, Speed);
}

void ACar_Pawn::SetPosition_Multicast_Implementation()
{
	Position.X += Speed;
	OnRep_SetPosition();
}

void ACar_Pawn::SetUpPosition_Multicast_Implementation(FVector p)
{
	Position = p;
	OnRep_SetPosition();
}

void ACar_Pawn::OnRep_SetPosition()
{
	SetActorLocation(Position);
	if (Position.X > 6500.0f)
	{
		Destroy();
	}
}