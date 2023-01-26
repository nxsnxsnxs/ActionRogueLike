// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "Components/Widget.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyGameBlueprintFunctionLibrary.generated.h"
class ABaseProjectile;
/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API UMyGameBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	UFUNCTION(BlueprintCallable)
	static int ApplyDamageWithImpulse(class UCharacterAttributeComponent* AttributeComponent, float DeltaVal, AActor* InstigateActor, const FHitResult& HitResult, float ImpulseVal);
	UFUNCTION(BlueprintCallable)
	static const UGameplayEffect* GetGameplayEffectFromSpec(const FGameplayEffectSpec& GESpec);
	UFUNCTION(BlueprintCallable)
	static UWidget* CreateEngineWidget(TSubclassOf<UWidget> WidgetClass, UUserWidget* WidgetOuter);
	UFUNCTION(BlueprintCallable)
	static bool CanActivateAbilityByHandle(UAbilitySystemComponent* ASC, FGameplayAbilitySpecHandle AbilitySpecHandle);
};
