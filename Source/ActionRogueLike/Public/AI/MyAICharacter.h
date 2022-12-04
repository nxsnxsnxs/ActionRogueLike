// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyAICharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAICharacterDie, AMyAICharacter*, AICharacter, AActor*, Killer);

UCLASS()
class ACTIONROGUELIKE_API AMyAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyAICharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:
	UPROPERTY(BlueprintAssignable)
	FOnAICharacterDie OnAICharacterDie;
protected:
	UFUNCTION()
	virtual void OnSeePawn(APawn* Pawn);
	UFUNCTION()
	virtual void OnDie(AActor* Killer);
	UFUNCTION()
	virtual void OnHealthChange(AActor* InstigateActor, int DeltaVal, int CurrHealth);
	void SetAttackTarget(AActor* Target);
protected:
	UPROPERTY(VisibleAnywhere)
	class UPawnSensingComponent* PawnSensingComponent;
	UPROPERTY(VisibleAnywhere)
	class UCharacterAttributeComponent* AttributeComponent;
};
