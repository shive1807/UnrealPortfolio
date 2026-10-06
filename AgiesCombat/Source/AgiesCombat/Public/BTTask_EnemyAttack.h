
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_EnemyAttack.generated.h"

UCLASS()
class AGIESCOMBAT_API UBTTask_EnemyAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_EnemyAttack();

	virtual EBTNodeResult::Type ExecuteTask(
		UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory
	) override;
};