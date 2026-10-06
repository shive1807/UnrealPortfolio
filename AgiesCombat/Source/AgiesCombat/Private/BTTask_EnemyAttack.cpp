
#include "BTTask_EnemyAttack.h"

#include "AIController.h"
#include "CombatComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "GameFramework/Pawn.h"

UBTTask_EnemyAttack::UBTTask_EnemyAttack()
{
	NodeName = TEXT("Enemy Attack");
}

EBTNodeResult::Type UBTTask_EnemyAttack::ExecuteTask(
	UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		return EBTNodeResult::Failed;
	}

	APawn* Enemy = AIController->GetPawn();
	if (!Enemy)
	{
		return EBTNodeResult::Failed;
	}

	UCombatComponent* Combat =
		Enemy->FindComponentByClass<UCombatComponent>();

	if (!Combat)
	{
		UE_LOG(
			LogTemp,
			Warning,
			TEXT("Enemy Attack failed: CombatComponent missing on %s"),
			*Enemy->GetName()
		);

		return EBTNodeResult::Failed;
	}

	Combat->Attack();

	return EBTNodeResult::Succeeded;
}