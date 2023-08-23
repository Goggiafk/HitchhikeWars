// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCBTTask_FindRandomLocation.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UNPCBTTask_FindRandomLocation::UNPCBTTask_FindRandomLocation()
{
	NodeName = TEXT("Find Random Location");

	// Accept only vectors
	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(
		UNPCBTTask_FindRandomLocation, BlackboardKey));
}

EBTNodeResult::Type UNPCBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FNavLocation Location{};

	AAIController* AIController {OwnerComp.GetAIOwner()};
	const APawn* AIPawn {AIController->GetPawn()};

	const FVector Origin {AIPawn->GetActorLocation()};

	const UNavigationSystemV1* NavSystem {UNavigationSystemV1::GetCurrent(GetWorld())};
	if(IsValid(NavSystem) && NavSystem->GetRandomPointInNavigableRadius(Origin, WalkRadius, Location))
	{
		AIController->GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, Location.Location);
	}

	// Signal the BehaviorTreeComponent that the task finished with a success
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return  EBTNodeResult::Succeeded;
}

FString UNPCBTTask_FindRandomLocation::GetStaticDescription() const
{
	return  FString::Printf(TEXT("Vector: &s"), *BlackboardKey.SelectedKeyName.ToString());
}
