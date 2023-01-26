// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MyGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API UMyGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
protected:
	virtual void ApplyCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const override;
private:
	UPROPERTY(EditDefaultsOnly, Category="Cooldowns", meta=(ToolTip="The Duration of cooldown effect, 0 means use effect default"))
	float CooldownDuration;
};