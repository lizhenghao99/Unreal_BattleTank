// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "TankAimingComponent.h"

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

	if (!ensure(PlayerTank && ControlledTank)) { return; }

	// move towards player
	MoveToActor(PlayerTank, AcceptanceRadius);

	// aim at player
	UTankAimingComponent* AimingComponent = 
		ControlledTank->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	// fire at player
	AimingComponent->Fire();
}
