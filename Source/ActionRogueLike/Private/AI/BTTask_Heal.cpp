// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_Heal.h"

#include "AIController.h"
#include "CharacterAttributeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

UBTTask_Heal::UBTTask_Heal()
{
	INIT_TASK_NODE_NOTIFY_FLAGS();
}

EBTNodeResult::Type UBTTask_Heal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIC = OwnerComp.GetAIOwner();
	UBlackboardComponent* BlackboardComponent = AIC->GetBlackboardComponent();
	AActor* SelfActor = AIC->GetPawn();
	if(SelfActor == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	UCharacterAttributeComponent* AttributeComponent = SelfActor->FindComponentByClass<UCharacterAttributeComponent>();
	if(AttributeComponent == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	BlackboardComponent->SetValueAsFloat("LastHealTime", UGameplayStatics::GetTimeSeconds(this));
	return EBTNodeResult::InProgress;
}

void UBTTask_Heal::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* AIC = OwnerComp.GetAIOwner();
	UBlackboardComponent* BlackboardComponent = AIC->GetBlackboardComponent();
	AActor* SelfActor = AIC->GetPawn();
	if(SelfActor == nullptr)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}
	EBTNodeResult::Type Result = Heal(SelfActor, DeltaSeconds);
	if(Result != EBTNodeResult::InProgress)
	{
		FinishLatentTask(OwnerComp, Result);
	}
}

EBTNodeResult::Type UBTTask_Heal::Heal(AActor* TargetActor, float DeltaSeconds)
{
	UCharacterAttributeComponent* AttributeComponent = TargetActor->FindComponentByClass<UCharacterAttributeComponent>();
	if(AttributeComponent == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	float DeltaHealth = HealScale * DeltaSeconds;
	AttributeComponent->ApplyHealthChange(DeltaHealth, AttributeComponent->GetOwner());
	if(AttributeComponent->GetMaxHealth() == AttributeComponent->GetHealth())
	{
		return EBTNodeResult::Succeeded;
	}
	else return EBTNodeResult::InProgress;
}
