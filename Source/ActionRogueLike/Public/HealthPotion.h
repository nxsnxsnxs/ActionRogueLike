// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "HealthPotion.generated.h"

UCLASS()
class ACTIONROGUELIKE_API AHealthPotion : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHealthPotion();
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	UPROPERTY(EditAnywhere)
	int HealingPower;
protected:
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* Mesh;
};
