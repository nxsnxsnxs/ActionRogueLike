// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseProjectile.h"
#include "AI/MyAICharacter.h"
#include "UI/WorldUserWidget.h"
#include "Minion.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API AMinion : public AMyAICharacter
{
	GENERATED_BODY()
public:
	AMinion();
	void DoMeleeAttack(APawn* Target);
	void DoRangedAttack(APawn* Target);
	//Anim Check
	UFUNCTION(BlueprintCallable)
	bool InMeleeAttack() const { return bInMeleeAttack; }
	UFUNCTION(BlueprintCallable)
	bool InRangedAttack() const { return bInRangedAttack; }
	//Anim Event Call
	UFUNCTION(BlueprintCallable)
	void OnMeleeAttackFinish();
	UFUNCTION(BlueprintCallable)
	void OnRangedAttackFinish();
protected:
	virtual void OnHealthChange(AActor* InstigateActor, int DeltaVal, int CurrHealth) override;
	virtual void OnSeePawn(APawn* Pawn) override;
	virtual void OnDie(AActor* Damager) override;
protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABaseProjectile> ProjectileClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UWorldUserWidget> HealthWidgetClass;
	UPROPERTY(BlueprintReadWrite)
	UWorldUserWidget* HealthWidget;
	UPROPERTY(EditDefaultsOnly)
	int ShootSpread;
	bool bInMeleeAttack;
	bool bInRangedAttack;
};
