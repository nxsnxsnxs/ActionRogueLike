// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExplosiveBarrel.generated.h"

UCLASS()
class ACTIONROGUELIKE_API AExplosiveBarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExplosiveBarrel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	void Explode();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(VisibleAnywhere)
	class URadialForceComponent* RadialForceComponent;
	UPROPERTY(EditDefaultsOnly)
	class UParticleSystem* ExplodeParticle;
	UPROPERTY(EditDefaultsOnly)
	class USoundBase* ExplodeSound;
	UPROPERTY(EditDefaultsOnly)
	float ExplodeRadius;
	UPROPERTY(EditDefaultsOnly)
	float ExplodeDamage;
};
