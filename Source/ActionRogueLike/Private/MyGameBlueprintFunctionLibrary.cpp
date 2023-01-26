// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameBlueprintFunctionLibrary.h"

#include "AbilitySystemComponent.h"
#include "CharacterAttributeComponent.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Kismet/GameplayStatics.h"

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

const UGameplayEffect* UMyGameBlueprintFunctionLibrary::GetGameplayEffectFromSpec(const FGameplayEffectSpec& GESpec)
{
	return GESpec.Def.Get();
}

UWidget* UMyGameBlueprintFunctionLibrary::CreateEngineWidget(TSubclassOf<UWidget> WidgetClass, UUserWidget* WidgetOuter)
{
	return WidgetOuter->WidgetTree->ConstructWidget<UWidget>(WidgetClass);
}

bool UMyGameBlueprintFunctionLibrary::CanActivateAbilityByHandle(UAbilitySystemComponent* ASC,
	FGameplayAbilitySpecHandle AbilitySpecHandle)
{
	if(ensure(ASC))
	{
		FGameplayAbilitySpec* AbilitySpec = ASC->FindAbilitySpecFromHandle(AbilitySpecHandle);
		if(ensure(AbilitySpec))
		{
			UGameplayAbility* Ability = AbilitySpec->Ability;
			return Ability->CanActivateAbility(AbilitySpecHandle, ASC->AbilityActorInfo.Get());
		}
	}
	return false;
}
