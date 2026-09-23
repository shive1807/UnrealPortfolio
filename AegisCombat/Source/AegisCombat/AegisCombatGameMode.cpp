// Copyright Epic Games, Inc. All Rights Reserved.

#include "AegisCombatGameMode.h"
#include "AegisCombatCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAegisCombatGameMode::AAegisCombatGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
