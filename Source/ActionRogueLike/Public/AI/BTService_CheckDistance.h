// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_CheckDistance.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API UBTService_CheckDistance : public UBTService
{
	GENERATED_BODY()
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
protected:
	UPROPERTY(EditAnywhere)
	bool bNeedLOS;
	UPROPERTY(EditAnywhere)
	float MinDistance = 0;
	UPROPERTY(EditAnywhere)
	float MaxDistance = 1e9;
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector TargetKey;
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector ResultKey;
};
