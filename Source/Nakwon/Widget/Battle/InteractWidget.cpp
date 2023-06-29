// Fill out your copyright notice in the Description page of Project Settings.


#include "../Battle/InteractWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"

#include "../../GameInstance/MyGameInstance.h"
#include "../../PlayerState/BattlePlayerState.h"
#include "../../Item/ItemBase.h"

void UInteractWidget::InitWidget()
{
	UE_LOG(LogTemp, Warning, TEXT("UInteractWidget::InitWidget"));
	MenuArray.Add(Brd_Equip);
	MenuArray.Add(Brd_Use);
	MenuArray.Add(Brd_Take);
	MenuArray.Add(Brd_Examine);

	HideInteractMenu();
}

void UInteractWidget::ShowInteractMenu(FName ItemName)
{
	if (ItemName.IsNone())
	{
		UE_LOG(LogTemp, Error, TEXT("UInteractWidget::ShowInteractMenu : ItemName is None"));
		return;
	}
	if (FItemInfo* ItemInfo = GetGameInstance<UMyGameInstance>()->FindItemInfo(ItemName))
	{
		ABattlePlayerState* PlayerState = GetOwningPlayerState<ABattlePlayerState>();
		if (!PlayerState)
		{
			UE_LOG(LogTemp, Error, TEXT("UInteractWidget::ShowInteractMenu : PlayerState is not valid"));
			return;
		}

		Img_CrossHair->SetVisibility(ESlateVisibility::Visible);
		TB_ItemName->SetVisibility(ESlateVisibility::Visible);
		Brd_Menu->SetVisibility(ESlateVisibility::Visible);
		if (PlayerState->IsKnowItem(ItemName))
		{
			TB_ItemName->SetText(FText::FromName(ItemInfo->ItemName));

			if (ItemInfo->ItemType == EItemType::CONSUMABLE)
			{
				// Check ConsumableType Use, Drink, 
				// TB_Use->SetText();
				MenuArray[(int)EItemAct::USE-1]->SetVisibility(ESlateVisibility::Visible);
			}
			else if (ItemInfo->ItemType == EItemType::EQUIPMENT)
			{
				MenuArray[(int)EItemAct::Equip-1]->SetVisibility(ESlateVisibility::Visible);
			}

			MenuArray[(int)EItemAct::TAKE-1]->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			TB_ItemName->SetText(FText::FromName(TEXT("Unkown")));
			MenuArray[(int)EItemAct::EXAMINE-1]->SetVisibility(ESlateVisibility::Visible);
		}

		ActiveFirstMenu();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UInteractWidget::ShowInteractMenu : Cannot Find Item in DataTable"));
		return;
	}
}

void UInteractWidget::HideInteractMenu()
{
	Img_CrossHair->SetVisibility(ESlateVisibility::Collapsed);
	TB_ItemName->SetVisibility(ESlateVisibility::Collapsed);
	Brd_Menu->SetVisibility(ESlateVisibility::Collapsed);
	for (int i = 0; i < MenuArray.Num(); ++i)
	{
		MenuArray[i]->SetVisibility(ESlateVisibility::Collapsed);
		MenuArray[i]->SetBrushColor(FLinearColor(1, 1, 1, 0));
		FSlateColor Color = TB_ItemName->GetColorAndOpacity();
		Cast<UTextBlock>(MenuArray[i]->GetChildAt(0))->SetColorAndOpacity(FLinearColor(1, 1, 1, 1));
	}
}

void UInteractWidget::ActiveFirstMenu()
{
	for (int32 i = 0; i < MenuArray.Num(); ++i)
	{
		if (MenuArray[i]->GetVisibility() == ESlateVisibility::Visible)
		{
			MenuArray[i]->SetBrushColor(FLinearColor(1, 1, 1, 0.6));
			Cast<UTextBlock>(MenuArray[i]->GetChildAt(0))->SetColorAndOpacity(FLinearColor(0, 0, 0, 1));
			break;
		}
	}
}