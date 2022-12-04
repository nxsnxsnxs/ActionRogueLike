// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_MeleeAttack_Minion.h"

#include "AIController.h"
#include "AI/Minion.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_MeleeAttack_Minion::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	AAIController* OwnerController = OwnerComp.GetAIOwner();
	AMinion* OwnerMinion = Cast<AMinion>(OwnerController->GetPawn());
	if(OwnerMinion == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	APawn* TargetPawn = Cast<APawn>(BlackboardComponent->GetValueAsObject("AttackTarget"));
	if(TargetPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	OwnerMinion->DoMeleeAttack(TargetPawn);
	return EBTNodeResult::Succeeded;
}
