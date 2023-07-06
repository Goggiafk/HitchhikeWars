// Copyright Epic Games, Inc. All Rights Reserved.

#include "HitchhikeWarsGameMode.h"
#include "HitchhikeWarsCharacter.h"
#include "UObject/ConstructorHelpers.h"

AHitchhikeWarsGameMode::AHitchhikeWarsGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
