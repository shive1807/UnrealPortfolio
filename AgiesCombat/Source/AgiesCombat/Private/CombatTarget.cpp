// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatTarget.h"
#include "TimerManager.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "Animation/AnimInstance.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
ACombatTarget::ACombatTarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

float ACombatTarget::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	if (!HealthComponent || DamageAmount <= 0)
	{
		return 0.0f;
	}

	HealthComponent->ApplyDamage(DamageAmount);

	return DamageAmount;
}


// Called when the game starts or when spawned
void ACombatTarget::BeginPlay()
{
	Super::BeginPlay();

	if (HealthComponent)
	{
		HealthComponent->OnHit.AddDynamic(this, &ACombatTarget::HandleHit);
		
		HealthComponent->OnDeath.AddDynamic(this, &ACombatTarget::HandleDeath);
	}
}

// Called every frame
void ACombatTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACombatTarget::HandleDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("%s handling death"), *GetName());

	// Prevent HandleDeath from running more than once.
	if (bIsDead)
	{
		return;
	}

	bIsDead = true;

	//stop this enemy AI
	if (AAIController* AIController = Cast<AAIController>(GetController()))
	{
		AIController->StopMovement();
		AIController->ClearFocus(EAIFocusPriority::Gameplay);

		if (AIController->BrainComponent)
		{
			AIController->BrainComponent->StopLogic(TEXT("Enemy Died"));
			UE_LOG(LogTemp, Warning, TEXT("%s AI stopped because enemy died"), *GetName());
		}
	}

	// Stop the death target from interacting with the world.
	SetActorEnableCollision(false);

	UE_LOG(LogTemp, Warning, TEXT("%s is now dead"), *GetName());
}

void ACombatTarget::HandleHit()
{
	UE_LOG(LogTemp, Warning, TEXT("%s received a hit."), *GetName());

	if (!HitReactionMontage)
	{
		return;
	}	

	USkeletalMeshComponent* Mesh = FindComponentByClass<USkeletalMeshComponent>();

	if (!Mesh)
	{
		return;
	}

	UAnimInstance* AnimInstance = Mesh->GetAnimInstance();
	if (!AnimInstance)
	{
		return;
	}

	//temp log
	UE_LOG(LogTemp, Warning, TEXT("Playing hit reaction montage on %s"), *GetName());
	AnimInstance->Montage_Play(HitReactionMontage);
}

bool ACombatTarget::IsDead() const
{
	return bIsDead;
}