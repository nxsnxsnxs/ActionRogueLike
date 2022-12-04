// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyGameBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API UMyGameBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	UFUNCTION(BlueprintCallable)
	static int ApplyDamageWithImpulse(class UCharacterAttributeComponent* AttributeComponent, float DeltaVal, AActor* InstigateActor, const FHitResult& HitResult, float ImpulseVal);
};
