// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseProjectile.h"
#include "BlackHoleProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ABlackHoleProjectile : public ABaseProjectile
{
	GENERATED_BODY()
public:
	ABlackHoleProjectile();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Explode();
protected:
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int Damage;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class URadialForceComponent* RadialForceComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<AActor*> SwallowedActors;
};
