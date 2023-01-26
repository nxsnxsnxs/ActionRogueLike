// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/SizeBox.h"
#include "WorldUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API UWorldUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void Init(AActor* _AttachedActor, FVector _WorldOffset);
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	AActor* AttachedActor;
	UPROPERTY(EditDefaultsOnly)
	FVector WorldOffset;
	UPROPERTY(meta=(BindWidget))
	USizeBox* ParentSizeBox;
};
