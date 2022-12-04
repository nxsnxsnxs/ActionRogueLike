// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractComponent.h"

#include "Interactable.h"

// Sets default values for this component's properties
UInteractComponent::UInteractComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UInteractComponent::Interact()
{
	FVector EyeLocation;
	FRotator EyeRotation;
	AActor* Owner = GetOwner();
	Owner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
	FVector End = EyeLocation + EyeRotation.Vector() * InteractRange;
	
	FCollisionObjectQueryParams QueryParams;
	QueryParams.AddObjectTypesToQuery(ECC_WorldStatic);

	float InteractSize = 30.0f;
	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(InteractSize);
	
	FHitResult HitResult;
	GetWorld()->SweepSingleByObjectType(HitResult, EyeLocation, End, FQuat::Identity, QueryParams, CollisionShape);
	if(HitResult.bBlockingHit)
	{
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, InteractSize, 32, FColor::Red, false, 2.0f, 0, 2.0f);
		if(HitResult.GetActor()->Implements<UInteractable>())
		{
			IInteractable::Execute_Interact(HitResult.GetActor(), Cast<APawn>(Owner));
		}
	}
	
}


// Called when the game starts
void UInteractComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

