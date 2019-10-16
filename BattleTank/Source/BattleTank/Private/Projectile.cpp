// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// projectile movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(
		FName("Projectile Movement"));
	ProjectileMovement->bAutoActivate = false;

	// collision mesh
	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(
		FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);

	// launch blast
	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(
		FName("Launch Blast"));
	LaunchBlast->AttachToComponent(RootComponent, 
		FAttachmentTransformRules::KeepRelativeTransform);

	// impact blast
	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(
		FName("Impact Blast"));
	ImpactBlast->AttachToComponent(RootComponent,
		FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->bAutoActivate = false;

	// explosion force
	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(
		FName("Explosion Force"));
	ExplosionForce->AttachToComponent(RootComponent,
		FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, FVector NormalImpulse,
	const FHitResult& Hit)
{
	LaunchBlast->Deactivate();
	ImpactBlast->Activate();
	ExplosionForce->FireImpulse();
	// destroy mesh
	SetRootComponent(ImpactBlast);
	CollisionMesh->DestroyComponent();
	// deal damage
	UGameplayStatics::ApplyRadialDamage(
		this, ProjectileDamage, GetActorLocation(), ExplosionForce->Radius,
		UDamageType::StaticClass(),
		TArray<AActor*>() // ignore no actors
	);
	// destroy projectile
	FTimerHandle Timer;
	GetWorld()->GetTimerManager().SetTimer(Timer, this,
		&AProjectile::OnTimerExpire, DestroyDelay, false);
}

void AProjectile::OnTimerExpire()
{
	Destroy();
}


// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::LaunchProjectile(float Speed)
{
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovement->Activate();
}