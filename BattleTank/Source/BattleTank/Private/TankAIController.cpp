// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// get player tank
	ATank* PlayerTank = Cast<ATank>(
		GetWorld()->GetFirstPlayerController()->GetPawn());
	// get controlled tank
	ATank* ControlledTank = Cast<ATank>(GetPawn());

	if (PlayerTank)
	{
		// aim at player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		// fire at player
		ControlledTank->fire();
	}
}
