// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h" // to implement tank on death

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// get player tank
	APawn* PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	// get controlled tank
	APawn* ControlledTank = GetPawn();

	if (!(PlayerTank && ControlledTank)) { return; }

	// move towards player
	MoveToActor(PlayerTank, AcceptanceRadius);

	// aim at player
	UTankAimingComponent* AimingComponent = 
		ControlledTank->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	// if aiming locked
	// fire at player
	if (AimingComponent->GetFiringState() == EFiringState::Locked)
	{
		AimingComponent->Fire();
	}
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		ATank* PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }
		// Subscribe to tank death event
		PossessedTank->OnDeath.AddUniqueDynamic(
			this, &ATankAIController::OnPossessedTankDeath);
	}
}

void ATankAIController::OnPossessedTankDeath()
{
	if (!GetPawn()) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();
}
