// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatTarget.h"
#include "TimerManager.h"

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
	SetActorEnableCollision(false);
}

void ACombatTarget::HandleHit()
{
	UE_LOG(LogTemp, Warning, TEXT("%s received a hit."), *GetName());

	//temp rotates the target when hit
	

	//Temp hit reaction
	//Will replace it with animation later. 
	const FRotator CurrentRotation = GetActorRotation();

	SetActorRotation(CurrentRotation + FRotator(0.0f, 10.0f, 0.0f));
}