// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Minion.h"

#include "AIController.h"
#include "CharacterAttributeComponent.h"
#include "MyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AMinion::AMinion()
{
	PrimaryActorTick.bCanEverTick = true;

	ShootSpread = 4;
}

void AMinion::DoMeleeAttack(APawn* Target)
{
	bInMeleeAttack = true;
	UCharacterAttributeComponent* CharacterAttributeComponent = Cast<UCharacterAttributeComponent>(Target->GetComponentByClass(UCharacterAttributeComponent::StaticClass()));
	if(ensure(CharacterAttributeComponent))
	{
		CharacterAttributeComponent->ApplyHealthChange(-30, this);
	}
}

void AMinion::DoRangedAttack(APawn* Target)
{
	bInRangedAttack = true;
	FVector FireLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	FRotator ShootDir = UKismetMathLibrary::MakeRotFromX(Target->GetActorLocation() - FireLocation);
	ShootDir.Pitch += FMath::RandRange(0, ShootSpread);
	ShootDir.Yaw += FMath::RandRange(-ShootSpread, ShootSpread);
	FTransform SpawnTM(ShootDir, FireLocation);
	
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParameters.Instigator = this;
	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParameters);
}

void AMinion::OnMeleeAttackFinish()
{
	bInMeleeAttack = false;
}

void AMinion::OnRangedAttackFinish()
{
	bInRangedAttack = false;
}

void AMinion::OnHealthChange(AActor* InstigateActor, int DeltaVal, int CurrHealth)
{
	Super::OnHealthChange(InstigateActor, DeltaVal, CurrHealth);
	
	if(DeltaVal < 0)
	{
		if(Cast<AMyCharacter>(InstigateActor)) SetAttackTarget(InstigateActor);
		if(HealthWidget == nullptr)
		{
			HealthWidget = CreateWidget<UWorldUserWidget>(GetWorld(), HealthWidgetClass);
			if(HealthWidget != nullptr)
			{
				HealthWidget->Init(this, FVector(0, 0, GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));
				HealthWidget->AddToViewport();
			}
		}
	}
}

void AMinion::OnSeePawn(APawn* Pawn)
{
	Super::OnSeePawn(Pawn);
	
	AAIController* OwnerController = Cast<AAIController>(GetController());
	if(ensure(OwnerController))
	{
		UBlackboardComponent* BlackboardComponent = OwnerController->GetBlackboardComponent();
		BlackboardComponent->SetValueAsObject("AttackTarget", Pawn);
	}
}

void AMinion::OnDie(AActor* Damager)
{
	Super::OnDie(Damager);

	if(HealthWidget)
	{
		HealthWidget->RemoveFromParent();
	}
}
