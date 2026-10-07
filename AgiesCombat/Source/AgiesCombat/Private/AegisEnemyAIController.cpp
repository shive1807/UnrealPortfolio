#include "AegisEnemyAIController.h"

#include "AgiesCombatGameState.h"
#include "BrainComponent.h"

AAegisEnemyAIController::AAegisEnemyAIController()
{
}

void AAegisEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UE_LOG(LogTemp, Warning, TEXT("AegisEnemyAIController possessed: %s"), *GetNameSafe(InPawn));

	AAgiesCombatGameState* GameState = GetWorld()->GetGameState<AAgiesCombatGameState>();
	if (!GameState)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find AgiesCombatGameState"));
		return;
	}

	GameState->OnPlayerDied.AddDynamic(this, &AAegisEnemyAIController::OnPlayerDied);
	UE_LOG(LogTemp, Warning, TEXT("Enemy AI subscribed to Player Died event"));
	
	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
	}
}

void AAegisEnemyAIController::OnPlayerDied()
{
	UE_LOG(LogTemp, Warning, TEXT("PLAYER DIEd - STOPPING ENEMY AI "));

	StopMovement();
	ClearFocus(EAIFocusPriority::Gameplay);

	if (BrainComponent)
	{
		BrainComponent->StopLogic(TEXT("Player died"));
		UE_LOG(LogTemp, Warning, TEXT("Enemy BrainComponent stopped."));
	}
}
