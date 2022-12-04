// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_CheckDistance.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTService_CheckDistance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	AActor* Target = Cast<AActor>(BlackboardComponent->GetValueAsObject(TargetKey.SelectedKeyName));
	if(Target == nullptr)
	{
		BlackboardComponent->SetValueAsBool(ResultKey.SelectedKeyName, false);
		return;
	}
	AActor* SelfActor = Cast<AActor>(BlackboardComponent->GetValueAsObject("SelfActor"));
	AAIController* SelfController = OwnerComp.GetAIOwner();
	float Dist = FVector::Distance(SelfActor->GetActorLocation(), Target->GetActorLocation());
	bool bInRange = (MinDistance <= Dist && Dist <= MaxDistance);
	bool bHasLOS = false;
	if(bInRange && bNeedLOS)
	{
		bHasLOS = SelfController->LineOfSightTo(Target);
	}
	BlackboardComponent->SetValueAsBool(ResultKey.SelectedKeyName, bInRange && (!bNeedLOS || bHasLOS));
}
