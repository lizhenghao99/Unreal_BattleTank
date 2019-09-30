// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// calculate slippage speed (sideway component of velocity)
	float SlippageSpeed = FVector::DotProduct(
		GetRightVector(), GetComponentVelocity());
	// work-out the required acceleration this frame to corrects
	FVector CorrectionAcceleration = -(SlippageSpeed / DeltaTime) * GetRightVector();
	// calculate and apply sideway force
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	FVector CorrectionForce =
		(TankRoot->GetMass() * CorrectionAcceleration) / 2;
	TankRoot->AddForce(CorrectionForce);
}

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