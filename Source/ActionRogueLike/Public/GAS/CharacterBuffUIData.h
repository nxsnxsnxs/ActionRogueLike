// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectUIData.h"
#include "CharacterBuffUIData.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API UCharacterBuffUIData : public UGameplayEffectUIData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTexture2D* BuffIcon;
};
