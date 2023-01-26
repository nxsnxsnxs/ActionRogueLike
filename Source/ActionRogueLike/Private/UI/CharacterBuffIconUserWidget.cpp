// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CharacterBuffIconUserWidget.h"

#include "AbilitySystemComponent.h"
#include "GAS/CharacterBuffUIData.h"

void UCharacterBuffIconUserWidget::Init(UAbilitySystemComponent* SourceComp, const FGameplayEffectSpec& GESpec, FActiveGameplayEffectHandle AttachedActiveGEHandle)
{
	UAbilitySystemComponent* ASC = AttachedActiveGEHandle.GetOwningAbilitySystemComponent();
	FActiveGameplayEffect* ActiveGE = const_cast<FActiveGameplayEffect*>(ASC->GetActiveGameplayEffect(AttachedActiveGEHandle));
	ActiveGE->EventSet.OnEffectRemoved.AddUObject(this, &UCharacterBuffIconUserWidget::OnAttachedBuffRemoved);

	UCharacterBuffUIData* BuffUIData = Cast<UCharacterBuffUIData>(GESpec.Def->UIData);
	if(BuffUIData)
	{
		BuffIconImage->SetBrushFromTexture(BuffUIData->BuffIcon, true);
	}
}

void UCharacterBuffIconUserWidget::OnAttachedBuffRemoved(const FGameplayEffectRemovalInfo& RemovalInfo)
{
	RemoveFromParent();
}
