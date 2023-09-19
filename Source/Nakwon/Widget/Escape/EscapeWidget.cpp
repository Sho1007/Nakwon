// Fill out your copyright notice in the Description page of Project Settings.


#include "../Escape/EscapeWidget.h"

#include "../InGameMenu/InGameMenuWidget.h"
#include "InteractWidget.h"
#include "../Escape/EscapeProgressWidget.h"

void UEscapeWidget::Init()
{
	EscapeProgressWidget->Init();
}

FText UEscapeWidget::GetSelectInteractText() const
{
	return InteractWidget->GetSelectInteractText();
}

void UEscapeWidget::ShowInteractMenu(const TArray<FText>& MenuTextArray, FText InteractActorName)
{
	InteractWidget->ShowInteractMenu(MenuTextArray, InteractActorName);
}

void UEscapeWidget::HideItemMenu()
{
	InteractWidget->HideInteractMenu();
}

void UEscapeWidget::SelectMenu()
{
	InteractWidget->SelectMenu();
}

void UEscapeWidget::ToggleInGameMenu()
{
	InGameMenuWidget->Toggle();
}

void UEscapeWidget::ShowEscapeProgress()
{
	EscapeProgressWidget->SetVisibility(ESlateVisibility::Visible);
}

void UEscapeWidget::HideEscapeProgress()
{
	EscapeProgressWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void UEscapeWidget::SetRenderTarget(UMaterialInstanceDynamic* NewMaterial)
{
	InGameMenuWidget->SetRenderTarget(NewMaterial);
}