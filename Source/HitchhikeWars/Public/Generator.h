// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Generator.generated.h"

class UBoxComponent;
UCLASS()
class HITCHHIKEWARS_API AGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGenerator();

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	void MulticastAddToProgressBar(float ValueToAdd);
	
	UFUNCTION(BlueprintCallable)
	void AddToProgressBar(float ValueToAdd);
	bool MulticastAddToProgressBar_Validate(float ValueToAdd);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float InitialProgressBarValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated, Category = "UI")
	float CurrentProgressBarValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* WidgetComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DecreaseValue;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComponent;

private:
	

	UFUNCTION()
	void DecreaseProgressBar();
	
	FTimerHandle TimerHandle_DecreaseProgressBar;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
