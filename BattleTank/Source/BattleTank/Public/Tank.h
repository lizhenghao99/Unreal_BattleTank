// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Particles/ParticleSystemComponent.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called by engine when actor takes damage event triggered
	virtual float TakeDamage(
		float DamageAmount, 
		struct FDamageEvent const& DamageEvent, 
		class AController* EventInstigator,
		AActor* DamageCauser) override;

	// return health as percentage
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;

	// Dynamic Multicast Delegate
	FTankDelegate OnDeath;

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(UParticleSystemComponent* DeathFireToSet);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth; // initialised in beginplay

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* DeathFire = nullptr;
};
