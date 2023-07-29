// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletActor.h"
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
	ATP_ThirdPersonCharacter* MyCharacter = Cast<ATP_ThirdPersonCharacter>(OtherActor);
	if (MyCharacter)
	{
		// Cast successful. Use the BP_ThirdPerson functionality here.
	}
	else if (OtherActor && OtherActor != this)
	{
		if(ImpactEffect)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
		}

		if (ImpactSound)
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, Hit.ImpactPoint);
		}

		OtherActor->Destroy();

		Destroy();
	}
}



