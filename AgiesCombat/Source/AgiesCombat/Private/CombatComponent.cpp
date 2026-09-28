// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatComponent.h"
#include "DrawDebugHelpers.h"

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

	UE_LOG(LogTemp, Warning, TEXT("%s attacked for %.1f damage"), *GetOwner()->GetName(), AttackDamage);

	PerformAttackTrace();
	CombatState = ECombatState::Idle;
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
		ECC_Visibility,
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
		UE_LOG(LogTemp, Warning, TEXT("Attack hit: %s"), *HitResult.GetActor()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Attack Missed"));
	}
}
