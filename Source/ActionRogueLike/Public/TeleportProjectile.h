// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseProjectile.h"
#include "GameplayEffect.h"
#include "TeleportProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ATeleportProjectile : public ABaseProjectile
{
	GENERATED_BODY()
public:
	ATeleportProjectile();
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintNativeEvent)
	void Explode();
	virtual void Explode_Implementation();
	virtual void Teleport();
protected:
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> BounceArmorEffectClass;
	UPROPERTY(EditDefaultsOnly)
	float BounceArmorDuration;
	UPROPERTY(EditDefaultsOnly, meta=(ToolTip="Seconds Before Explode After Throw"))
	float ExplodeTime;
	UPROPERTY(EditDefaultsOnly, meta=(ToolTip="Seconds Between Explode And Teleport"))
	float TeleportTime;
	FTimerHandle ExplodeTimerHandle;
	FTimerHandle TeleportTimerHandle;
};
