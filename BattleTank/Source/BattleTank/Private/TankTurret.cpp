// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	// clamp relative speed
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0, 1.0);

	// rotation change per frame
	float RotationChange =
		RelativeSpeed * MaxDegreesPerSeconds * GetWorld()->DeltaTimeSeconds;

	// elevation after change this frame
	float RawNewRotation = RelativeRotation.Yaw + RotationChange;

	// rotate turret
	SetRelativeRotation(FRotator(0, RawNewRotation, 0));
}