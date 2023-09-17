// Fill out your copyright notice in the Description page of Project Settings.


#include "../InGameMenu/InGameMenuWidget.h"

// Test : Weapon Modify
#include <Components/Image.h>
#include <Engine/TextureRenderTarget2D.h>

void UInGameMenuWidget::SetUp()
{
	this->SetVisibility(ESlateVisibility::Collapsed);
}

void UInGameMenuWidget::Toggle()
{
	if (GetVisibility() == ESlateVisibility::Visible)
	{
		if (APlayerController* PC = GetOwningPlayer())
		{
			PC->SetInputMode(FInputModeGameOnly());
			PC->SetShowMouseCursor(false);
		}
		this->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		if (APlayerController* PC = GetOwningPlayer())
		{
			PC->SetInputMode(FInputModeGameAndUI());
			PC->SetShowMouseCursor(true);
		}
		this->SetVisibility(ESlateVisibility::Visible);
	}
}

void UInGameMenuWidget::SetRenderTarget(UMaterialInstanceDynamic* NewMaterial)
{
	Image_WeaponModifyTest->SetBrushFromMaterial(NewMaterial);
}