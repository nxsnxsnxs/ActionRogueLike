// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_CheckSensedTarget.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API UBTService_CheckSensedTarget : public UBTService
{
	GENERATED_BODY()
public:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
protected:
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector TargetKey;
};
