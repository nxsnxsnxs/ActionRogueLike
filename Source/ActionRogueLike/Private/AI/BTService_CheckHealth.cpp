// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_CheckHealth.h"

#include "AIController.h"
#include "CharacterAttributeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTService_CheckHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* AIC = OwnerComp.GetAIOwner();
	UBlackboardComponent* BlackboardComponent = AIC->GetBlackboardComponent();
	AActor* TargetActor = Cast<AActor>(BlackboardComponent->GetValueAsObject(TargetActorKey.SelectedKeyName));
	if(TargetActor == nullptr)
	{
		return;
	}
	UCharacterAttributeComponent* AttributeComponent = TargetActor->FindComponentByClass<UCharacterAttributeComponent>();
	if(AttributeComponent == nullptr)
	{
		return;
	}
	int CurrHealth = AttributeComponent->GetHealth();

	BlackboardComponent->SetValueAsBool(BlackboardKey.SelectedKeyName, CurrHealth >= HealthThreshold * AttributeComponent->GetMaxHealth());
}
