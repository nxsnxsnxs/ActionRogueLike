// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_CheckSensedTarget.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/PawnSensingComponent.h"

void UBTService_CheckSensedTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* AIC = OwnerComp.GetAIOwner();
	UBlackboardComponent* BlackboardComponent = AIC->GetBlackboardComponent();
	APawn* Target = Cast<APawn>(BlackboardComponent->GetValueAsObject(TargetKey.SelectedKeyName));
	APawn* SelfPawn = AIC->GetPawn();
	if(Target == nullptr)
	{
		return;
	}
	UPawnSensingComponent* PawnSensingComponent = Cast<UPawnSensingComponent>(SelfPawn->GetComponentByClass(UPawnSensingComponent::StaticClass()));
    if(ensure(PawnSensingComponent) && PawnSensingComponent->CouldSeePawn(Target) && AIC->LineOfSightTo(Target))
    {
	    return;
    }
	BlackboardComponent->SetValueAsObject(TargetKey.SelectedKeyName, nullptr);
}
