// Fill out your copyright notice in the Description page of Project Settings.


#include "../HUD/BattleHUD.h"

#include "../Widget/Battle/InteractWidget.h"
#include "../Widget/Battle/InteractMenuSlotWidget.h"

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

void ABattleHUD::BeginPlay()
{
	Super::BeginPlay();
	if (InteractWidgetClass)
	{
		InteractWidget = CreateWidget<UInteractWidget>(GetWorld()->GetFirstPlayerController(), InteractWidgetClass, FName(TEXT("InteractWidget")));
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