#include "BTService_FindPlayer.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

UBTService_FindPlayer::UBTService_FindPlayer()
{
	NodeName = TEXT("Find Player");

	// Run every half second.
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

	UE_LOG(
		LogTemp,
		Warning,
		TEXT("FindPlayer: Found player %s"),
		*Player->GetName()
	);

	Blackboard->SetValueAsObject(
		TEXT("TargetActor"),
		Player
	);
}