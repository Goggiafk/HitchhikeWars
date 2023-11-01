// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Pawn.h"
#include "Components/SkeletalMeshComponent.h"
#include "Car_Pawn.generated.h"

UCLASS()
class HITCHHIKEWARS_API ACar_Pawn : public APawn
{
	GENERATED_BODY()
public:
	ACar_Pawn();

	UFUNCTION(NetMulticast, Reliable)
	void SetUpPosition_Multicast(FVector p);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(ReplicatedUsing = OnRep_SetPosition)
	FVector Position;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	USkeletalMeshComponent* SkeletalMeshComponent;

	UFUNCTION(NetMulticast, Reliable)
	void SetUpCar_Multicast();

	UFUNCTION()
	void OnRep_SetUpCar();

	UPROPERTY(ReplicatedUsing = OnRep_SetUpCar)
	USkeletalMesh* CurrentCarMesh;

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;

	UFUNCTION(NetMulticast, Reliable)
	void SetPosition_Multicast();

	UFUNCTION()
	void OnRep_SetPosition();

private:
	UPROPERTY(EditAnywhere, Category = "Car Parameters")
	TArray<USkeletalMesh*> CarMeshes;
	
	UPROPERTY(ReplicatedUsing = OnRep_SetUpCar)
	float Speed;
};

