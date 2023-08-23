// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "BulletActor.generated.h"

UCLASS()
class HITCHHIKEWARS_API ABulletActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABulletActor();
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovement;

protected:

	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(Server, Reliable)
	void BulletHit_Server(AActor* OtherActor, const FHitResult& Hit);

	UFUNCTION(NetMulticast, Reliable)
	void BulletHit_Multicast(AActor* OtherActor, const FHitResult& Hit);

	UFUNCTION(Server, Reliable)
	void PlayerHit_Server(ATP_ThirdPersonCharacter* Character);

	UFUNCTION(NetMulticast, Reliable)
	void PlayerHit_Multicast(ATP_ThirdPersonCharacter* Character);

	
	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* ImpactEffect;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* ImpactSound;
};
