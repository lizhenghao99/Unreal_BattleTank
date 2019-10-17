// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// impact blast
	//DeathFire = CreateDefaultSubobject<UParticleSystemComponent>(
	//	FName("Death Fire"));
//	DeathFire->bAutoActivate = false;
}


void ATank::Initialise(UParticleSystemComponent* DeathFireToSet)
{
	DeathFire = DeathFireToSet;
	DeathFire->bAutoActivate = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = StartingHealth;
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// round input float to int
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	// clamp to max health
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;

	if (CurrentHealth <= 0)
	{
		OnDeath.Broadcast();
		DeathFire->Activate();
	}

	return (float)DamageToApply;
}

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth;
}