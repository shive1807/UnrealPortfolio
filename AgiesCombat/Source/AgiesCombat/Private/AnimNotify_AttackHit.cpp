#include "AnimNotify_AttackHit.h"

#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Actor.h"
#include "CombatComponent.h"

void UAnimNotify_AttackHit::Notify(
	USkeletalMeshComponent* MeshComp,
	UAnimSequenceBase* Animation)
{
	if (!MeshComp)
	{
		return;
	}

	AActor* Owner = MeshComp->GetOwner();

	if (!Owner)
	{
		return;
	}

	UCombatComponent* CombatComponent =
		Owner->FindComponentByClass<UCombatComponent>();

	if (CombatComponent)
	{
		CombatComponent->PerformAttackHit();
	}
}