// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MyAICharacter.h"

#include "AIController.h"
#include "BrainComponent.h"
#include "CharacterAttributeComponent.h"
#include "MyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
AMyAICharacter::AMyAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");
	AttributeComponent = CreateDefaultSubobject<UCharacterAttributeComponent>("AttributeComp");
}

// Called when the game starts or when spawned
void AMyAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PawnSensingComponent->OnSeePawn.AddDynamic(this, &AMyAICharacter::OnSeePawn);
	AttributeComponent->OnDie.AddDynamic(this, &AMyAICharacter::OnDie);
	AttributeComponent->OnHealthChange.AddDynamic(this, &AMyAICharacter::OnHealthChange);
}

// Called every frame
void AMyAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyAICharacter::OnSeePawn(APawn* Pawn)
{
	
}

void AMyAICharacter::OnDie(AActor* Killer)
{
	AAIController* AIC = Cast<AAIController>(GetController());
	AIC->GetBrainComponent()->StopLogic("Dead");
	
	GetMesh()->SetAllBodiesSimulatePhysics(true);
	GetMesh()->SetCollisionProfileName("Ragdoll");
	
	SetLifeSpan(8);

	OnAICharacterDie.Broadcast(this, Killer);
}

void AMyAICharacter::OnHealthChange(AActor* InstigateActor, int DeltaVal, int CurrHealth)
{

}

void AMyAICharacter::SetAttackTarget(AActor* Target)
{
	AAIController* OwnerController = Cast<AAIController>(GetController());
	if(ensure(OwnerController))
	{
		UBlackboardComponent* BlackboardComponent = OwnerController->GetBlackboardComponent();
		BlackboardComponent->SetValueAsObject("AttackTarget", Target);
	}
}

