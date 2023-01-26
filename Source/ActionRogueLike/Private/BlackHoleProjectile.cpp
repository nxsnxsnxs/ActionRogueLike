// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackHoleProjectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

ABlackHoleProjectile::ABlackHoleProjectile()
{
	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>("RadialForceComp");
	RadialForceComponent->SetupAttachment(RootComponent);

	ProjectileMovementComponent->InitialSpeed = 600.0f;
	ProjectileMovementComponent->MaxSpeed = 600.0f;
	ProjectileMovementComponent->ProjectileGravityScale = 0;
}

void ABlackHoleProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABlackHoleProjectile::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
}

void ABlackHoleProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	Explode();
	Super::OnHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
}
