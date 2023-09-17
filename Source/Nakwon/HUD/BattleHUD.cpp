// Fill out your copyright notice in the Description page of Project Settings.


#include "../HUD/BattleHUD.h"

#include "../Widget/Battle/InteractWidget.h"
#include "../Widget/InGameMenu/InGameMenuWidget.h"

FText ABattleHUD::GetSelectInteractText() const
{
	return InteractWidget->GetSelectInteractText();
}

void ABattleHUD::ShowInteractMenu(const TArray<FText>& MenuTextArray, FText InteractActorName)
{	
	InteractWidget->ShowInteractMenu(MenuTextArray, InteractActorName);
}

void ABattleHUD::HideItemMenu()
{
	InteractWidget->HideInteractMenu();
}

void ABattleHUD::SelectMenu(float WheelValue)
{
	InteractWidget->SelectMenu(WheelValue);
}

void ABattleHUD::ToggleInGameMenu()
{
	InGameMenuWidget->Toggle();
}

void ABattleHUD::SetRenderTarget(UMaterialInstanceDynamic* NewMaterial)
{
	InGameMenuWidget->SetRenderTarget(NewMaterial);
}

void ABattleHUD::BeginPlay()
{
	Super::BeginPlay();
	if (InteractWidgetClass)
	{
		InteractWidget = CreateWidget<UInteractWidget>(GetWorld()->GetFirstPlayerController(), InteractWidgetClass, FName(TEXT("InteractWidget")));
		if (InteractWidget)
		{
			InteractWidget->InitWidget();
			InteractWidget->AddToViewport(0);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("ABattleHUD::BeginPlay : Create InteractWidget Failed"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ABattleHUD::BeginPlay : InteractWidgetClass is NULL"));
	}

	if (InGameMenuWidgetClass)
	{
		InGameMenuWidget = CreateWidget<UInGameMenuWidget>(GetWorld()->GetFirstPlayerController(), InGameMenuWidgetClass, FName(TEXT("InGameMenuWidget")));
		if (InGameMenuWidget)
		{
			InGameMenuWidget->SetUp();
			InGameMenuWidget->AddToViewport(0);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("ABattleHUD::BeginPlay : Create InGameMenuWidget Failed"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ABattleHUD::BeginPlay : InGameMenuWidgetClass is NULL"));
	}
}