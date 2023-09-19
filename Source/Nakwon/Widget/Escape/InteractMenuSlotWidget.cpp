// Fill out your copyright notice in the Description page of Project Settings.


#include "../Escape/InteractMenuSlotWidget.h"

#include "Components/TextBlock.h"
#include "Components/Border.h"

FText UInteractMenuSlotWidget::GetText() const
{
	return TB_Slot->GetText();
}

void UInteractMenuSlotWidget::SetText(const FText& NewText)
{
	TB_Slot->SetText(NewText);
}

void UInteractMenuSlotWidget::SetFocus(bool bIsFocused)
{
	if (bIsFocused)
	{
		Brd_Slot->SetBrushColor(FLinearColor(1, 1, 1, 0.8));
		TB_Slot->SetColorAndOpacity(FLinearColor(0, 0, 0, 1));
	}
	else
	{
		Brd_Slot->SetBrushColor(FLinearColor(1, 1, 1, 0.0));
		TB_Slot->SetColorAndOpacity(FLinearColor(1, 1, 1, 1));
	}
}