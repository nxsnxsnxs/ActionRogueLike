// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameBlueprintFunctionLibrary.h"

#include "CharacterAttributeComponent.h"

int UMyGameBlueprintFunctionLibrary::ApplyDamageWithImpulse(UCharacterAttributeComponent* AttributeComponent,
                                                            float DeltaVal, AActor* InstigateActor, const FHitResult& HitResult, float ImpulseVal)
{
	int ActualDamage = AttributeComponent->ApplyHealthChange(DeltaVal, InstigateActor);
	if(ActualDamage)
	{
		UPrimitiveComponent* TargetPrimitive = HitResult.GetComponent();
		if(TargetPrimitive && TargetPrimitive->IsSimulatingPhysics(HitResult.BoneName))
		{
			FVector Impulse = -HitResult.ImpactNormal * ImpulseVal;
			TargetPrimitive->AddImpulse(Impulse, HitResult.BoneName);
		}
	}
	return ActualDamage;
}
