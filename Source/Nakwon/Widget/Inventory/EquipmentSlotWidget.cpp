// Fill out your copyright notice in the Description page of Project Settings.


#include "../Inventory/EquipmentSlotWidget.h"

#include <Components/Border.h>
#include <Components/SizeBox.h>
#include <Components/TextBlock.h>

bool UEquipmentSlotWidget::Initialize()
{
	if (Super::Initialize() == false) return false;
	
	SizeBox->SetWidthOverride(Width);
	SizeBox->SetHeightOverride(Height);

	SlotNameTextBlock->SetText(SlotName);

	return true;
}

void UEquipmentSlotWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (GEngine)
	{
		if (const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EEquipmentType"), true))
		{
			GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Yellow, FString::Printf(TEXT("%s Entered"), *EnumPtr->GetNameStringByValue((int64)EquipmentType)));
		}
	}
}

void UEquipmentSlotWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	if (GEngine)
	{
		if (const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EEquipmentType"), true))
		{
			GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Yellow, FString::Printf(TEXT("%s Leaved"), *EnumPtr->GetNameStringByValue((int64)EquipmentType)));
		}
	}
}