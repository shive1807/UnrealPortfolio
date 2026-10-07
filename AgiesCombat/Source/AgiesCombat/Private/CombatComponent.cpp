// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "Animation/AnimInstance.h"
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
    UE_LOG(LogTemp, Warning, TEXT("========== ATTACK START =========="));

    if (!CanAttack())
    {
        UE_LOG(LogTemp, Warning, TEXT("Attack blocked: CanAttack() returned FALSE"));
        return;
    }

    CombatState = ECombatState::Attacking;
    LastAttackTime = GetWorld()->GetTimeSeconds();

    UE_LOG(
        LogTemp,
        Warning,
        TEXT("%s started attack | CombatState = Attacking"),
        *GetOwner()->GetName()
    );

    if (!AttackMontage)
    {
        UE_LOG(LogTemp, Error, TEXT("AttackMontage is NULL!"));
        return;
    }

    UE_LOG(
        LogTemp,
        Warning,
        TEXT("AttackMontage found: %s"),
        *AttackMontage->GetName()
    );

    ACharacter* Character = Cast<ACharacter>(GetOwner());

    if (!Character)
    {
        UE_LOG(
            LogTemp,
            Error,
            TEXT("Failed to cast Owner to ACharacter! Owner: %s"),
            *GetOwner()->GetName()
        );
        return;
    }

    UE_LOG(
        LogTemp,
        Warning,
        TEXT("Character cast successful: %s"),
        *Character->GetName()
    );

    if (!Character->GetMesh())
    {
        UE_LOG(LogTemp, Error, TEXT("Character Mesh is NULL!"));
        return;
    }

    UE_LOG(
        LogTemp,
        Warning,
        TEXT("Character Mesh: %s"),
        *Character->GetMesh()->GetName()
    );

    UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();

    if (!AnimInstance)
    {
        UE_LOG(LogTemp, Error, TEXT("AnimInstance is NULL!"));
        return;
    }

    UE_LOG(
        LogTemp,
        Warning,
        TEXT("AnimInstance found: %s"),
        *AnimInstance->GetName()
    );

    const float MontageLength = Character->PlayAnimMontage(AttackMontage);

    UE_LOG(
        LogTemp,
        Warning,
        TEXT("PlayAnimMontage() returned: %f"),
        MontageLength
    );

    if (MontageLength <= 0.0f)
    {
        UE_LOG(
            LogTemp,
            Error,
            TEXT("Attack montage DID NOT PLAY! Return value: %f"),
            MontageLength
        );
    }
    else
    {
        UE_LOG(
            LogTemp,
            Warning,
            TEXT("Attack montage started successfully!")
        );
    }

    FOnMontageEnded MontageEndedDelegate;
    MontageEndedDelegate.BindUObject(
        this,
        &UCombatComponent::OnAttackMontageEnded
    );

    AnimInstance->Montage_SetEndDelegate(
        MontageEndedDelegate,
        AttackMontage
    );

    UE_LOG(
        LogTemp,
        Warning,
        TEXT("Montage end delegate registered.")
    );

    UE_LOG(LogTemp, Warning, TEXT("========== ATTACK END =========="));
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

void UCombatComponent::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (Montage != AttackMontage)
	{
		return;
	}

	CombatState = ECombatState::Idle;

	UE_LOG(LogTemp, Warning, TEXT("Attack montage ended. CombatState reset to Idle"));
}

