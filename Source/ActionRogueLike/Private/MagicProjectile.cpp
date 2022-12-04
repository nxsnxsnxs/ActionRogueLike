// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AMagicProjectile::AMagicProjectile()
{
	ProjectileMovementComponent->InitialSpeed = 1200.0f;
	ProjectileMovementComponent->MaxSpeed = 1200.0f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.2f;
}

// Called when the game starts or when spawned
void AMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

