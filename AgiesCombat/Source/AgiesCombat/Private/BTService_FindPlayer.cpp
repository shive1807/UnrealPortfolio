#include "BTService_FindPlayer.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

UBTService_FindPlayer::UBTService_FindPlayer()
{
    NodeName = TEXT("Find Player");
    Interval = 0.5f;
    RandomDeviation = 0.0f;
}

void UBTService_FindPlayer::TickNode(
    UBehaviorTreeComponent& OwnerComp,
    uint8* NodeMemory,
    float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    UBlackboardComponent* Blackboard =
        OwnerComp.GetBlackboardComponent();

    if (!Blackboard)
    {
        return;
    }

    ACharacter* Player =
        UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

    if (!Player)
    {
        return;
    }

    Blackboard->SetValueAsObject(
        TEXT("TargetActor"),
        Player
    );
}