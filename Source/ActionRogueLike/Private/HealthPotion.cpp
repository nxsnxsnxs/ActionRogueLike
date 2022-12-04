// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPotion.h"

#include "CharacterAttributeComponent.h"

// Sets default values
AHealthPotion::AHealthPotion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	RootComponent = Mesh;
}

void AHealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	UCharacterAttributeComponent* AttributeComponent = Cast<UCharacterAttributeComponent>(InstigatorPawn->GetComponentByClass(UCharacterAttributeComponent::StaticClass()));
	if(AttributeComponent)
	{
		if(AttributeComponent->GetHealth() != AttributeComponent->GetMaxHealth())
		{
			AttributeComponent->ApplyHealthChange(HealingPower, this);
			Destroy();
		}
	}
}

// Called when the game starts or when spawned
void AHealthPotion::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHealthPotion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

