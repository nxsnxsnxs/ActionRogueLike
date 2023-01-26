// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/MyGameplayAbility.h"

#include "AbilitySystemComponent.h"

void UMyGameplayAbility::ApplyCooldown(const FGameplayAbilitySpecHandle Handle,
                                       const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const
{
	UGameplayEffect* CooldownGE = GetCooldownGameplayEffect();
	if (CooldownGE)
	{
		float GameplayEffectLevel = GetAbilityLevel(Handle, ActorInfo);
		if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
		{
			FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(Handle, ActorInfo, ActivationInfo, CooldownGE->GetClass(), GameplayEffectLevel);
			if (SpecHandle.IsValid())
			{
				SpecHandle.Data->StackCount = 1;
				if(CooldownDuration)
				{
					SpecHandle.Data->SetDuration(CooldownDuration, true);
				}
				ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, SpecHandle);
			}
		}
	}
}
