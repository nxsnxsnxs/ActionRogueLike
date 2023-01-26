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
	if(FocusedActor)
	{
		IInteractable::Execute_Interact(FocusedActor, Cast<APawn>(GetOwner()));
	}
}


// Called when the game starts
void UInteractComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UInteractComponent::CheckInteract()
{
	FocusedActor = nullptr;
	
	FVector EyeLocation;
	FRotator EyeRotation;
	AActor* Owner = GetOwner();
	Owner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
	FVector End = EyeLocation + EyeRotation.Vector() * InteractRange;
	
	FCollisionObjectQueryParams QueryParams;
	QueryParams.AddObjectTypesToQuery(InteractChannel);
	
	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(InteractRadius);
	
	FHitResult HitResult;
	GetWorld()->SweepSingleByObjectType(HitResult, EyeLocation, End, FQuat::Identity, QueryParams, CollisionShape);
	if(HitResult.bBlockingHit)
	{
		if(CVarDebugShowInteractTrace->GetBool())
		{
			DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, InteractRadius, 32, FColor::Red, false, 2.0f, 0, 2.0f);
		}
		if(HitResult.GetActor()->Implements<UInteractable>())
		{
			FocusedActor = HitResult.GetActor();
			if(!TipWidget && ensure(TipWidgetClass))
			{
				TipWidget = CreateWidget<UWorldUserWidget>(GetWorld(), TipWidgetClass);
			}
			if(!TipWidget->IsInViewport())
			{
				TipWidget->Init(FocusedActor, FVector::Zero());
				TipWidget->AddToViewport();
			}
		}
		else if(TipWidget)
		{
			TipWidget->RemoveFromParent();
		}
	}
	else if(TipWidget)
	{
		TipWidget->RemoveFromParent();
	}
}


// Called every frame
void UInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CheckInteract();
}

