// Fill out your copyright notice in the Description page of Project Settings.


#include "../Battle/InteractWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "Components/VerticalBox.h"

#include "../../GameInstance/MyGameInstance.h"
#include "../../PlayerState/BattlePlayerState.h"
#include "../../Item/ItemBase.h"
#include "InteractMenuSlotWidget.h"
void UInteractWidget::InitWidget()
{
	HideInteractMenu();
}

void UInteractWidget::ShowInteractMenu(const TArray<FText>& MenuTextArray, FText InteractActorName)
{
	if (MenuTextArray.Num() == 0) return;

	Img_CrossHair->SetVisibility(ESlateVisibility::Visible);

	if (InteractActorName.IsEmpty() == false)
	{
		TB_ItemName->SetVisibility(ESlateVisibility::Visible);
		TB_ItemName->SetText(InteractActorName);
	}

	Brd_Menu->SetVisibility(ESlateVisibility::Visible);

	check(InteractMenuSlotWidgetClass);

	FocusMenuNum = 0;
	for (int i = 0; i < MenuTextArray.Num(); ++i)
	{
		UInteractMenuSlotWidget* InteractMenuSlotWidget = CreateWidget<UInteractMenuSlotWidget>(GetWorld(), InteractMenuSlotWidgetClass);
		InteractMenuSlotWidget->SetText(MenuTextArray[i]);
		InteractMenuSlotWidget->SetFocus(i == FocusMenuNum);
		VB_Menu->AddChildToVerticalBox(InteractMenuSlotWidget);
	}

	for (int i = 0; i < VB_Menu->GetChildrenCount(); ++i)
	{
		UE_LOG(LogTemp, Warning, TEXT("%d Child : %s"), i, *Cast<UInteractMenuSlotWidget>(VB_Menu->GetChildAt(i))->GetText().ToString());
	}
}

void UInteractWidget::HideInteractMenu()
{
	Img_CrossHair->SetVisibility(ESlateVisibility::Collapsed);
	TB_ItemName->SetVisibility(ESlateVisibility::Collapsed);
	Brd_Menu->SetVisibility(ESlateVisibility::Collapsed);
	VB_Menu->ClearChildren();
}

void UInteractWidget::SelectMenu(float WheelValue)
{
	Cast<UInteractMenuSlotWidget>(VB_Menu->GetChildAt(FocusMenuNum))->SetFocus(false);

	FocusMenuNum = (FocusMenuNum + (int)WheelValue + VB_Menu->GetChildrenCount()) % VB_Menu->GetChildrenCount();

	Cast<UInteractMenuSlotWidget>(VB_Menu->GetChildAt(FocusMenuNum))->SetFocus(true);
}

FText UInteractWidget::GetSelectInteractText() const
{
	if (VB_Menu->GetChildrenCount() >= FocusMenuNum)
	{
		UE_LOG(LogTemp, Error, TEXT("UInteractWidget::GetSelectInteractText : Invalid Index"));
		return FText();
	}
	return Cast<UInteractMenuSlotWidget>(VB_Menu->GetChildAt(FocusMenuNum))->GetText();
}

void UInteractWidget::ActiveFirstMenu()
{
}