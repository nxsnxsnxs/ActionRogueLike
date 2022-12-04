// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleportProjectile.h"

#include "GameFramework/Character.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ATeleportProjectile::ATeleportProjectile()
{
	ProjectileMovementComponent->InitialSpeed = 1000.0f;
	ProjectileMovementComponent->MaxSpeed = 1000.0f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.25f;
}

void ATeleportProjectile::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(ExplodeTimerHandle, this, &ATeleportProjectile::Explode, ExplodeTime);
}

void ATeleportProjectile::Explode_Implementation()
{
	GetWorldTimerManager().ClearTimer(ExplodeTimerHandle);
	GetWorldTimerManager().SetTimer(TeleportTimerHandle, this, &ATeleportProjectile::Teleport, TeleportTime);
}

void ATeleportProjectile::Teleport()
{
	APawn* OwnerPlayer = GetInstigator();
	OwnerPlayer->TeleportTo(GetActorLocation(), OwnerPlayer->GetActorRotation());
	Destroy();
}

void ATeleportProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	Explode();
}
