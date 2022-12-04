// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MyAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void AMyAIController::BeginPlay()
{
	Super::BeginPlay();
	if(ensure(BehaviorTree))
	{
		RunBehaviorTree(BehaviorTree);
		UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();
		BlackboardComponent->SetValueAsObject("SelfActor", GetPawn());
	}
}
