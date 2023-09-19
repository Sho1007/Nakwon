// Fill out your copyright notice in the Description page of Project Settings.


#include "../Escape/InteractWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "Components/VerticalBox.h"

#include "../../GameInstance/MyGameInstance.h"
#include "../../PlayerState/BattlePlayerState.h"
#include "../../Item/ItemBase.h"
#include "InteractMenuSlotWidget.h"
#include "../../Character/MyCharacter.h"

void UInteractWidget::InitWidget()
{
	HideInteractMenu();
}

void UInteractWidget::ShowInteractMenu(const TArray<FText>& MenuTextArray, FText InteractActorName)
{
	UE_LOG(LogTemp, Warning, TEXT("UInteractWidget::ShowInteractMenu"));

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

	VB_Menu->ClearChildren();
	for (int i = 0; i < MenuTextArray.Num(); ++i)
	{
		UInteractMenuSlotWidget* InteractMenuSlotWidget = CreateWidget<UInteractMenuSlotWidget>(GetWorld(), InteractMenuSlotWidgetClass);
		InteractMenuSlotWidget->SetText(MenuTextArray[i]);
		InteractMenuSlotWidget->SetFocus(i == FocusMenuNum);
		VB_Menu->AddChildToVerticalBox(InteractMenuSlotWidget);
	}
}

void UInteractWidget::HideInteractMenu()
{
	Img_CrossHair->SetVisibility(ESlateVisibility::Collapsed);
	TB_ItemName->SetVisibility(ESlateVisibility::Collapsed);
	Brd_Menu->SetVisibility(ESlateVisibility::Collapsed);
}

void UInteractWidget::SelectMenu()
{
	Cast<UInteractMenuSlotWidget>(VB_Menu->GetChildAt(FocusMenuNum))->SetFocus(false);

	FocusMenuNum = GetOwningPlayerPawn<AMyCharacter>()->GetInteractMenuIndex();

	Cast<UInteractMenuSlotWidget>(VB_Menu->GetChildAt(FocusMenuNum))->SetFocus(true);
}

FText UInteractWidget::GetSelectInteractText() const
{
	if (VB_Menu->GetChildrenCount() <= FocusMenuNum)
	{
		UE_LOG(LogTemp, Error, TEXT("UInteractWidget::GetSelectInteractText : Invalid Index, FocusMenuNum : %d, MenuChildCount : %d"), FocusMenuNum, VB_Menu->GetChildrenCount());
		return FText();
	}
	return Cast<UInteractMenuSlotWidget>(VB_Menu->GetChildAt(FocusMenuNum))->GetText();
}

void UInteractWidget::ActiveFirstMenu()
{
}