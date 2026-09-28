// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatTarget.h"

// Sets default values
ACombatTarget::ACombatTarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

