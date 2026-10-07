// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "AgiesCombatGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDied);
/**
 * 
 */
UCLASS()
class AGIESCOMBAT_API AAgiesCombatGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Game Events")
	FOnPlayerDied OnPlayerDied;
};
