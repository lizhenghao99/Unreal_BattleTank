// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, FVector NormalImpulse, 
	const FHitResult& Hit)
{
	DriveTrack();
	ApplySidewaysForce();
	CurrentThrottle = 0;
}

void UTankTrack::ApplySidewaysForce()
{
	// calculate slippage speed (sideway component of velocity)
	float SlippageSpeed = FVector::DotProduct(
		GetRightVector(), GetComponentVelocity());
	// work-out the required acceleration this frame to corrects
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	FVector CorrectionAcceleration = -(SlippageSpeed / DeltaTime) * GetRightVector();
	// calculate and apply sideway force
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	FVector CorrectionForce =
		(TankRoot->GetMass() * CorrectionAcceleration) / 2;
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = CurrentThrottle + Throttle;
}

void UTankTrack::DriveTrack()
{
	// add force to tank from track
	FVector ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	// get tank root
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(
		GetOwner()->GetRootComponent());
	// apply force
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
