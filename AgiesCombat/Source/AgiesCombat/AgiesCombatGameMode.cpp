// Copyright Epic Games, Inc. All Rights Reserved.

#include "AgiesCombatGameMode.h"
#include "AgiesCombatGameState.h"
#include "UObject/ConstructorHelpers.h"

AAgiesCombatGameMode::AAgiesCombatGameMode()
{
	//set the custom GameState
	GameStateClass = AAgiesCombatGameState::StaticClass();
	
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
