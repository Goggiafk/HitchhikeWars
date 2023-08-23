// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ChasePlayer.h"

#include "AIController.h"
#include "NpcCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

UBTTask_ChasePlayer::UBTTask_ChasePlayer()
{
	NodeName = TEXT("Chase Player");

	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(
		UBTTask_ChasePlayer, BlackboardKey));
}

EBTNodeResult::Type UBTTask_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController {OwnerComp.GetAIOwner()};
	APawn* AIPawn = AIController->GetPawn();
	if (AIPawn)
	{
		UCharacterMovementComponent* CharacterMovement = AIPawn->FindComponentByClass<UCharacterMovementComponent>();
		if (CharacterMovement)
		{
			CharacterMovement->MaxWalkSpeed = RunSpeed;
		}
	}
	if (AIController)
	{
		// Get the player character
		ACharacter* PlayerCharacter {UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)};
		if (PlayerCharacter)
		{
			// Move towards the player's location
			FVector PlayerLocation {PlayerCharacter->GetActorLocation()};
			AIController->MoveToLocation(PlayerLocation);
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}

FString UBTTask_ChasePlayer::GetStaticDescription() const
{
	return Super::GetStaticDescription();
}
