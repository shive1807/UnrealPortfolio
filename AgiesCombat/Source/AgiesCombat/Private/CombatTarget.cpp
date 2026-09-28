// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatTarget.h"

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

	UE_LOG(LogTemp, Warning, TEXT("%s took %.1f damage"), *GetName(), DamageAmount);
	return DamageAmount;
}


// Called when the game starts or when spawned
void ACombatTarget::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACombatTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
