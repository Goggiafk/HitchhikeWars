// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "NPCBTTask_FindRandomLocation.generated.h"

/**
 * 
 */
UCLASS()
class HITCHHIKEWARS_API UNPCBTTask_FindRandomLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UNPCBTTask_FindRandomLocation();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search", meta = (AllowPrivateAccess = true))
	float WalkRadius = 500;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Walking", meta = (AllowPrivateAccess = true))
	float WalkSpeed = 500;
	
};
