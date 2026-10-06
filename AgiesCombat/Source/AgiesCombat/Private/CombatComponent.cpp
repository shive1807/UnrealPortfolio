// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCombatComponent::Attack()
{
	if (!CanAttack())
	{
		return;
	}

	CombatState = ECombatState::Attacking;
	LastAttackTime = GetWorld()->GetTimeSeconds();

	UE_LOG(LogTemp, Warning, TEXT("%s started attack"), *GetOwner()->GetName());

	if (AttackMontage)
	{
		if (ACharacter* Character = Cast<ACharacter>(GetOwner()))
		{
			Character->PlayAnimMontage(AttackMontage);
		}
	}
}

void UCombatComponent::PerformAttackHit()
{
	UE_LOG(LogTemp, Warning, TEXT("AttackHit notify triggered"));

	if (CombatState != ECombatState::Attacking)
	{
		UE_LOG(
			LogTemp,
			Warning,
			TEXT("AttackHit rejected - not attacking")
		);

		return;
	}
	
	PerformAttackTrace();
}

bool UCombatComponent::CanAttack() const
{
	if (CombatState != ECombatState::Idle)
	{
		return false;
	}

	if (!GetWorld())
	{
		return false;
	}

	const float CurrentTime = GetWorld()->GetTimeSeconds();
	return CurrentTime - LastAttackTime >= AttackCooldown;
}

ECombatState UCombatComponent::GetCombatState() const
{
	return CombatState;
}

void UCombatComponent::PerformAttackTrace()
{
	if (!GetOwner())
	{
		return;
	}

	FVector Start = GetOwner()->GetActorLocation();
	FVector Forward = GetOwner()->GetActorForwardVector();
	FVector End = Start + (Forward * AttackRange);
	FHitResult HitResult;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(GetOwner());

	const bool bHit = GetWorld()->LineTraceSingleByChannel(
    	HitResult,
    	Start,
    	End,
    	ECC_Pawn,
    	QueryParams);

	DrawDebugLine(
		GetWorld(),
		Start,
		End,
		FColor::Red,
		false,
		1.0f,
		0.0f,
		2.0f);

	if (bHit && HitResult.GetActor())
	{
		AActor* HitActor = HitResult.GetActor();
		
		UE_LOG(LogTemp, Warning, TEXT("Attack hit: %s"), *HitResult.GetActor()->GetName());

		UGameplayStatics::ApplyDamage(HitActor, AttackDamage, nullptr, GetOwner(), nullptr);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Attack Missed"));
	}
}

bool UCombatComponent::IsAttacking() const
{
	return CombatState == ECombatState::Attacking;
}
