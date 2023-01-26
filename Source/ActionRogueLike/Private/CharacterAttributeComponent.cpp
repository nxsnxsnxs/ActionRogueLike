// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAttributeComponent.h"

#include "GameFramework/Character.h"
#include "GameFramework/CheatManager.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UCharacterAttributeComponent::UCharacterAttributeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCharacterAttributeComponent::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;
	// ...
	
}


// Called every frame
void UCharacterAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

int UCharacterAttributeComponent::GetHealth() const
{
	return Health;
}

int UCharacterAttributeComponent::GetMaxHealth() const
{
	return MaxHealth;
}

void UCharacterAttributeComponent::SetMaxHealth(int _MaxHealth)
{
	MaxHealth = _MaxHealth;
}

int UCharacterAttributeComponent::ApplyHealthChange(float DeltaVal, AActor* InstigateActor)
{
	if(bDead || !GetOwner()->CanBeDamaged())
	{
		return 0;
	}
	DeltaVal *= CVarDebugDamageMultiplier.GetValueOnGameThread();
	float PrevHealth = Health;
	Health += DeltaVal;
	Health = UKismetMathLibrary::FClamp(Health, 0, MaxHealth);

	int RealDeltaInt = (int)Health - (int)PrevHealth;
	OnHealthChange.Broadcast(InstigateActor, RealDeltaInt, Health);
	UKismetSystemLibrary::PrintString(this, FString::FromInt(RealDeltaInt));
	//got damage
	if(DeltaVal < 0)
	{
		ACharacter* Owner = Cast<ACharacter>(GetOwner());
		if(Owner)
		{
			Owner->GetMesh()->SetScalarParameterValueOnMaterials("HitTime", UGameplayStatics::GetTimeSeconds(this));
		}
		//dead
		if(Health < 1.0f)
		{
			bDead = true;
			OnDie.Broadcast(InstigateActor);
		}
	}
	return RealDeltaInt;
}

bool UCharacterAttributeComponent::IsAlive() const
{
	return !bDead;
}

