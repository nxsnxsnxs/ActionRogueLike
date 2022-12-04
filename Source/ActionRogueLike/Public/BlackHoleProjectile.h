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
protected:
	UPROPERTY(VisibleAnywhere)
	class URadialForceComponent* RadialForceComponent;
};
