#include "BTDecorator_InAttackRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Actor.h"

UBTDecorator_InAttackRange::UBTDecorator_InAttackRange()
{
    NodeName = TEXT("In Attack Range");
}

bool UBTDecorator_InAttackRange::CalculateRawConditionValue(
    UBehaviorTreeComponent& OwnerComp,
    uint8* NodeMemory
) const
{
    const AAIController* AIController = OwnerComp.GetAIOwner();

    if (!AIController)
    {
        return false;
    }

    const APawn* Enemy = AIController->GetPawn();

    if (!Enemy)
    {
        return false;
    }

    const UBlackboardComponent* Blackboard =
        OwnerComp.GetBlackboardComponent();

    if (!Blackboard)
    {
        return false;
    }

    const AActor* Target =
        Cast<AActor>(
            Blackboard->GetValueAsObject(TEXT("TargetActor"))
        );

    if (!Target)
    {
        return false;
    }

    const float Distance =
        FVector::Dist(
            Enemy->GetActorLocation(),
            Target->GetActorLocation()
        );

    UE_LOG(
    LogTemp,
    Warning,
    TEXT("Attack Range Check: Distance = %.2f, AttackRange = %.2f"),
    Distance,
    AttackRange
);


    return Distance <= AttackRange;
}