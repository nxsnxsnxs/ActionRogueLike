// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UI/WorldUserWidget.h"
#include "InteractComponent.generated.h"

static TAutoConsoleVariable<bool> CVarDebugShowInteractTrace(TEXT("mygame_DebugShowInteractTrace"), false, TEXT("Show the trace collision of Character Interact"), ECVF_Cheat);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGUELIKE_API UInteractComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInteractComponent();
	void Interact();
protected:
	virtual void BeginPlay() override;
	void CheckInteract();
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
protected:
	UPROPERTY(EditDefaultsOnly)
	float InteractRange = 350.0f;
	UPROPERTY(EditDefaultsOnly)
	float InteractRadius = 30.0f;
	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<ECollisionChannel> InteractChannel;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UWorldUserWidget> TipWidgetClass;
	UPROPERTY()
	AActor* FocusedActor;
	UPROPERTY()
	UWorldUserWidget* TipWidget;
};
