// Fill out your copyright notice in the Description page of Project Settings.


#include "AgiesCombat/Public/HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	CurrentHealth = MaxHealth;
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
}

void UHealthComponent::ApplyDamage(float DamageAmount)
{
	if (DamageAmount <= 0.0f || CurrentHealth <= 0.0f)
	{
		return;
	}
	const float OldHealth = CurrentHealth;

	CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount,0.0f, MaxHealth);
	const float HealthDelta = CurrentHealth - OldHealth;
	OnHealthChanged.Broadcast(CurrentHealth, HealthDelta);

	UE_LOG(
		LogTemp,
		Warning,
		TEXT("%s took %.1f damage. Health: %.1f / %.1f"),
		*GetOwner()->GetName(),
		DamageAmount,
		CurrentHealth,
		MaxHealth
	);

	if (CurrentHealth <= 0.0f)
	{
		OnDeath.Broadcast();

		UE_LOG(
			LogTemp,
			Warning,
			TEXT("%s died"),
			*GetOwner()->GetName()
		);
	}
}

void UHealthComponent::Heal(float HealAmount)
{
	if (HealAmount <= 0.0f || CurrentHealth <= 0.0f)
	{
		return;
	}

	const float OldHealth = CurrentHealth;

	CurrentHealth = FMath::Clamp(CurrentHealth + HealAmount,0.0f, MaxHealth);

	const float HealthDelta = CurrentHealth - OldHealth;

	OnHealthChanged.Broadcast(CurrentHealth, HealthDelta);
}

float UHealthComponent::GetHealthPercent() const
{
	if (MaxHealth <= 0.0f)
	{
		return 0.0f;
	}

	return CurrentHealth / MaxHealth;
}
