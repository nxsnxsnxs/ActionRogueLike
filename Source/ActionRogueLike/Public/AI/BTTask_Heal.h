// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Heal.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API UBTTask_Heal : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_Heal();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	EBTNodeResult::Type Heal(AActor* TargetActor, float DeltaSeconds);
protected:
	UPROPERTY(EditAnywhere)
	float HealScale;
};
