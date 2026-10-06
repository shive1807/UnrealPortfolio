#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_InAttackRange.generated.h"

UCLASS()
class AGIESCOMBAT_API UBTDecorator_InAttackRange : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecorator_InAttackRange();

protected:
	virtual bool CalculateRawConditionValue(
		UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory
	) const override;

private:
	UPROPERTY(EditAnywhere, Category = "Combat")
	float AttackRange = 150.0f;
};