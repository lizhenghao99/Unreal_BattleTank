// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	//UE_LOG(LogTemp, Warning, TEXT("%f"), Throttle);
	// TODO: clamp force applied

	// add force to tank from track
	FVector ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	// get tank root
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(
		GetOwner()->GetRootComponent());
	// apply force
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}