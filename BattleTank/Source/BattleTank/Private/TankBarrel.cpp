// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	// clamp relative speed
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0, 1.0);

	// elevation change per frame
	float ElevationChange =
		RelativeSpeed * MaxDegreesPerSeconds * GetWorld()->DeltaTimeSeconds;

	// elevation after change this frame
	float RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	// clamp elevation
	float ClampedElevation = FMath::Clamp<float>(
		RawNewElevation, MinElevationDegrees, MaxElevationDegrees);

	// elevate barrel
	SetRelativeRotation(FRotator(ClampedElevation, 0, 0));
}