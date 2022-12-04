// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_CheckHealth.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API UBTService_CheckHealth : public UBTService
{
	GENERATED_BODY()
public:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
protected:
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector TargetActorKey;
	UPROPERTY(EditAnywhere)
	float HealthThreshold;
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector BlackboardKey;
};
