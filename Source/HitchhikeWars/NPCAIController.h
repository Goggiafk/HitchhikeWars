// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Components/CapsuleComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "NPCAIController.generated.h"

/**
 * 
 */
UCLASS()
class HITCHHIKEWARS_API ANPCAIController : public AAIController
{
	GENERATED_BODY()
	ANPCAIController();

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBehaviorTree> BehaviorTree;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBlackboardComponent> BlackboardComponent;
};
