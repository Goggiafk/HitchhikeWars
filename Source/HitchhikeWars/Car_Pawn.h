// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/SkeletalMeshComponent.h"
#include "Car_Pawn.generated.h"

UCLASS()
class HITCHHIKEWARS_API ACar_Pawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACar_Pawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	UPROPERTY(ReplicatedUsing = OnRep_SetPosition)
	FVector CarPosition;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	USkeletalMeshComponent* SkeletalMeshComponent;

	UFUNCTION(NetMulticast, Reliable)
	void SetUpCar_Multicast();

	UFUNCTION()
	void OnRep_SetUpCar();

	UPROPERTY(ReplicatedUsing = OnRep_SetUpCar)
	USkeletalMesh* CurrentCarMesh;

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;
	
public:

	UPROPERTY(EditAnywhere)
	TArray<USkeletalMesh*> car_meshes;
		
	UPROPERTY(ReplicatedUsing = OnRep_SetUpCar)
	float Speed;
	
	UFUNCTION(NetMulticast, Reliable)
	void SetPosition_Multicast();

	UFUNCTION(NetMulticast, Reliable)
	void SetUpPosition_Multicast(FVector p);
	
	UFUNCTION()
	void OnRep_SetPosition();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
