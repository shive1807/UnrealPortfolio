#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AegisEnemyAIController.generated.h"

UCLASS()
class AGIESCOMBAT_API AAegisEnemyAIController : public AAIController
{
    GENERATED_BODY()

public:
    AAegisEnemyAIController();

protected:
    virtual void OnPossess(APawn* InPawn) override;
};