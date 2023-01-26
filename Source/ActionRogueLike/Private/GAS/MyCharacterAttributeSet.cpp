// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/MyCharacterAttributeSet.h"

#include "GameplayEffectExtension.h"

void UMyCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	if(Attribute == GetEnduranceAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, GetMaxEndurance());
	}
	else if(Attribute == GetMovementSpeedAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, 10000);
	}
	else if(Attribute == GetRageValueAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, GetMaxRageValue());
	}
}

void UMyCharacterAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);
	if(Attribute == GetEnduranceAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, GetMaxEndurance());
	}
	else if(Attribute == GetMovementSpeedAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, 10000);
	}
	else if(Attribute == GetRageValueAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, GetMaxRageValue());
	}
}

void UMyCharacterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

}
