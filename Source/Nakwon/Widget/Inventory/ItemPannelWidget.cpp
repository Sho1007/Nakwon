// Fill out your copyright notice in the Description page of Project Settings.


#include "../Inventory/ItemPannelWidget.h"

#include <Components/TextBlock.h>
#include <Components/HorizontalBox.h>

#include "../../Item/ItemBase.h"
#include "../../Item/Equipment/EquipmentBase.h"

void UItemPannelWidget::InitWidget(AItemBase* TargetItem)
{
	FItemInfo ItemInfo = TargetItem->GetItemInfo();
	ItemName->SetText(ItemInfo.Name);
	if (ItemInfo.Type == EItemType::EQUIPMENT || ItemInfo.Type == EItemType::CONSUMABLE)
	{
		DurabilityHorizontalBox->SetVisibility(ESlateVisibility::Collapsed);
		MaxDurability->SetVisibility(ESlateVisibility::Collapsed);
		SlashText->SetVisibility(ESlateVisibility::Collapsed);
		DurabilityHorizontalBox->SetVisibility(ESlateVisibility::Collapsed);

		if (ItemInfo.Type == EItemType::EQUIPMENT)
		{
			// Equipment
			if (AEquipmentBase* Equipment = Cast<AEquipmentBase>(TargetItem))
			{
			}
		}
		else
		{
			// Consumable
		}
	}
}