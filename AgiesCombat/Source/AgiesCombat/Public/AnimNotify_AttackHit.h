#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_AttackHit.generated.h"

UCLASS()
class AGIESCOMBAT_API UAnimNotify_AttackHit : public UAnimNotify
{
	GENERATED_BODY()

public:

	virtual void Notify(
		USkeletalMeshComponent* MeshComp,
		UAnimSequenceBase* Animation
	) override;
};
