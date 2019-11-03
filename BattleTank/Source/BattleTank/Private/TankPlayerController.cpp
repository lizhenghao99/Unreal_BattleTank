// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	// find aiming component and broadcast event to bp
	UTankAimingComponent* AimingComponent =
		GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (AimingComponent)
	{
		FoundAimingComponent(AimingComponent);
	}
	else
	{
		UE_LOG(LogTemp, Error, 
			TEXT("Player controller cannot find aiming component"))
	}
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		ATank* PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }
		// Subscribe to tank death event
		PossessedTank->OnDeath.AddUniqueDynamic(
			this, &ATankPlayerController::OnPossessedTankDeath);
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("Player controller ticking"))
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; } // exit if not possessing a tank

	UTankAimingComponent* AimingComponent =
		GetPawn()->FindComponentByClass<UTankAimingComponent>(); 
	if (!ensure(AimingComponent)) { return; }

	FVector HitLocation; // out parameter
	// get line trace hit location from crosshair
	if (GetSightRayHitLocation(HitLocation))
	{
		AimingComponent->AimAt(HitLocation);
	}
}
	

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutLocation) const
{
	// find crosshair position on screen
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation(ViewportSizeX * CrosshairXLocation,
		ViewportSizeY * CrosshairYLocation);

	// de-project crosshair on screen location to world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// line-treace along look direction and see what is hit at max range
		return GetLookVectorHitLocation(LookDirection, OutLocation);
	}
	return false;
}

bool ATankPlayerController::GetLookDirection(
	FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation; // to be discarded
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y,
		CameraWorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(
	FVector& LookDirection, FVector& OutLocation) const
{
	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + LookDirection * LineTraceRange;
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Camera))
	{
		OutLocation = HitResult.Location;
		return true;
	}
	return false;
}

void ATankPlayerController::OnPossessedTankDeath()
{
	StartSpectatingOnly();
}
