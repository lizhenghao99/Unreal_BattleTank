// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/SphereComponent.h"
#include "SprungWheel.generated.h"

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddDrivingForce(float ForceMagnitude);

private:
	void SetupConstraints();

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* Wheel = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPhysicsConstraintComponent* Constraint = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* Axle = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPhysicsConstraintComponent* AxleConstraint = nullptr;
};
