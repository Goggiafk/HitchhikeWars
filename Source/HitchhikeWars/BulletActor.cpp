// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletActor.h"

#include "NpcCharacter.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TP_ThirdPerson/TP_ThirdPersonCharacter.h"

// Sets default values
ABulletActor::ABulletActor()
{
	PrimaryActorTick.bCanEverTick = false;

	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(5.0f);
	SphereComponent->SetCollisionProfileName("BlockAllDynamic");

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 2000;
	ProjectileMovement->MaxSpeed = 2000;
	ProjectileMovement->ProjectileGravityScale = 0;
	ProjectileMovement->bRotationFollowsVelocity = true;  

	SphereComponent->OnComponentHit.AddDynamic(this, &ABulletActor::OnProjectileHit);

	ImpactEffect = nullptr;
	ImpactSound = nullptr;
}

void ABulletActor::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor->IsA(ATP_ThirdPersonCharacter::StaticClass()))
	{
		ATP_ThirdPersonCharacter* MyCharacter = Cast<ATP_ThirdPersonCharacter>(OtherActor);
		if(MyCharacter)
		{
			PlayerHit_Server_Implementation(MyCharacter);
		}
	}
	else if (OtherActor && OtherActor->IsA(ANpcCharacter::StaticClass()))
	{
		ANpcCharacter* NpcCharacter = Cast<ANpcCharacter>(OtherActor);
		if(NpcCharacter)
		{
			NpcCharacter->TakeHealthDamage(50);
		}
	}
	
	if(ImpactEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
	}

	if (ImpactSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, Hit.ImpactPoint);
	}
	
	Destroy();
}

void ABulletActor::PlayerHit_Server_Implementation(ATP_ThirdPersonCharacter* Character)
{
	//PlayerHit_Multicast(Character);
	Character->TakeHealthDamage(10);
}

void ABulletActor::PlayerHit_Multicast_Implementation(ATP_ThirdPersonCharacter* Character)
{
	//Character->TakeHealthDamage(10);
}

void ABulletActor::BulletHit_Server_Implementation(AActor* OtherActor, const FHitResult& Hit)
{
	if(HasAuthority())
	{
		BulletHit_Multicast_Implementation(OtherActor, Hit);
	}
}

void ABulletActor::BulletHit_Multicast_Implementation(AActor* OtherActor, const FHitResult& Hit)
{
	
}




