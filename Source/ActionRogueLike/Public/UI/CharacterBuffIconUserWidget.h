// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "CharacterBuffIconUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API UCharacterBuffIconUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void Init(UAbilitySystemComponent* SourceComp, const FGameplayEffectSpec& GESpec, FActiveGameplayEffectHandle AttachedActiveGEHandle);
protected:
	void OnAttachedBuffRemoved(const FGameplayEffectRemovalInfo& RemovalInfo);
protected:
	UPROPERTY(meta=(BindWidget))
	UImage* BuffIconImage;
};
