// Copyright Epic Games, Inc. All Rights Reserved.

#include "AgiesCombatPortfolioGameMode.h"
#include "AgiesCombatPortfolioCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAgiesCombatPortfolioGameMode::AAgiesCombatPortfolioGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
