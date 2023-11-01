// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIHelpers.h"
#include "AITypes.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "Navigation/PathFollowingComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "NavigationSystem.h"
#include "TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "NpcCharacter.generated.h"

class UPawnSensingComponent;
UCLASS()
class HITCHHIKEWARS_API ANpcCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANpcCharacter();

	UPROPERTY(BlueprintReadWrite)
	ATP_ThirdPersonCharacter* ChasedPlayer;

	UFUNCTION()
	void ResetHasSeenPlayer();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPawnSensingComponent* PawnSensingComponent;

	UFUNCTION(BlueprintCallable)
	void SeesPlayer(APawn* SeenPlayer);
	void SetHasSeenPlayer(bool state);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxHealth = 100.0f;

	UPROPERTY(Replicated, BlueprintReadOnly)
	float CurrentHealth;

	bool bIsDead;

	void OnDeath();

private:
	FTimerHandle RetriggerableTimerHandle;
	FTimerDelegate RetriggerableTimerDelegate;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void NotifyActorBeginOverlap(AActor* OtherActor);
	void TakeHealthDamage(float DamageAmount);
};
