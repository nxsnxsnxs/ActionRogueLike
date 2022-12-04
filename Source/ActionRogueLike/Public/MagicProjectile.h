// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseProjectile.h"
#include "GameFramework/Actor.h"
#include "MagicProjectile.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDamagedTargetSignature, UCharacterAttributeComponent*, Target, int, Damage);

UCLASS()
class ACTIONROGUELIKE_API AMagicProjectile : public ABaseProjectile
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMagicProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
    FOnDamagedTargetSignature OnDamagedTarget;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Damage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float DamageImpulse;
};
