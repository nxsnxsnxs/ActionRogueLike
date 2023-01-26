// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterAttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnHealthChangeSignature, AActor*, InstigateActor, int, DeltaVal, int, CurrHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDieSignature, AActor*, Damager);

static TAutoConsoleVariable<float> CVarDebugDamageMultiplier(TEXT("mygame_DebugDamageMultiplier"), 1.0f, TEXT("Multiplier for all damage in game"), ECVF_Cheat);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGUELIKE_API UCharacterAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterAttributeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
	int GetHealth() const;
	UFUNCTION(BlueprintCallable)
	int GetMaxHealth() const;
	UFUNCTION(BlueprintCallable)
	void SetMaxHealth(int MaxHealth);
	UFUNCTION(BlueprintCallable)
	int ApplyHealthChange(float DeltaVal, AActor* InstigateActor);
	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;
public:
	UPROPERTY(BlueprintAssignable)
	FOnHealthChangeSignature OnHealthChange;
	UPROPERTY(BlueprintAssignable)
	FOnDieSignature OnDie;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Health;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxHealth = 100;
	UPROPERTY(BlueprintReadWrite)
	bool bDead;
};
