// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WorldUserWidget.h"

#include <Kismet/GameplayStatics.h>

#include "Blueprint/WidgetLayoutLibrary.h"

void UWorldUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	FVector WorldLocation = AttachedActor->GetActorLocation() + WorldOffset;
	FVector2d ScreenPos;
	if(UGameplayStatics::ProjectWorldToScreen(GetOwningPlayer(), WorldLocation, ScreenPos))
	{
		ScreenPos /= UWidgetLayoutLibrary::GetViewportScale(this);
		ParentSizeBox->SetRenderTranslation(ScreenPos);
	}
}
