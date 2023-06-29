// Fill out your copyright notice in the Description page of Project Settings.


#include "../HUD/BattleHUD.h"

#include "../Widget/Battle/InteractWidget.h"

void ABattleHUD::ShowInteractMenu(FName ItemName)
{
	InteractWidget->ShowInteractMenu(ItemName);
}

void ABattleHUD::HideItemMenu()
{
	InteractWidget->HideInteractMenu();
}

void ABattleHUD::BeginPlay()
{
	Super::BeginPlay();
	if (InteractWidgetClass)
	{
		InteractWidget = CreateWidget<UInteractWidget>(GetOwningPlayerController(), InteractWidgetClass, FName(TEXT("InteractWidget")));
		if (InteractWidget)
		{
			InteractWidget->InitWidget();
			InteractWidget->AddToPlayerScreen(0);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Create InteractWidget Failed"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("InteractWidgetClass is NULL"));
	}
}