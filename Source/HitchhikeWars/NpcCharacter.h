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
#include "NpcCharacter.generated.h"

class UPawnSensingComponent;
UCLASS()
class HITCHHIKEWARS_API ANpcCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANpcCharacter();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPawnSensingComponent* PawnSensingComponent;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
