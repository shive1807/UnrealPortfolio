#include "AegisEnemyAIController.h"

AAegisEnemyAIController::AAegisEnemyAIController()
{
}

void AAegisEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UE_LOG(
		LogTemp,
		Warning,
		TEXT("AegisEnemyAIController possessed: %s"),
		*GetNameSafe(InPawn)
	);

	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
	}
}