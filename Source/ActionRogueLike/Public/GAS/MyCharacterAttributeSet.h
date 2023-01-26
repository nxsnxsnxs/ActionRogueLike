// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "MyCharacterAttributeSet.generated.h"


#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API UMyCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
public:
	UPROPERTY()
	FGameplayAttributeData Endurance;
	ATTRIBUTE_ACCESSORS(UMyCharacterAttributeSet, Endurance);
	UPROPERTY()
	FGameplayAttributeData MaxEndurance;
	ATTRIBUTE_ACCESSORS(UMyCharacterAttributeSet, MaxEndurance);
	UPROPERTY()
	FGameplayAttributeData MovementSpeed;
	ATTRIBUTE_ACCESSORS(UMyCharacterAttributeSet, MovementSpeed);
	UPROPERTY()
	FGameplayAttributeData RageValue;
	ATTRIBUTE_ACCESSORS(UMyCharacterAttributeSet, RageValue);
	UPROPERTY()
	FGameplayAttributeData MaxRageValue;
	ATTRIBUTE_ACCESSORS(UMyCharacterAttributeSet, MaxRageValue);
};
