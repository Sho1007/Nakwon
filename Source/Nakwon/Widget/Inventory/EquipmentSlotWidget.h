// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../Nakwon.h"
#include "Blueprint/UserWidget.h"
#include "EquipmentSlotWidget.generated.h"

/**
 * 
 */
class UBorder;
class USizeBox;
class UTextBlock;
UCLASS()
class NAKWON_API UEquipmentSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	EEquipmentType EquipmentType;

	UPROPERTY(Meta = (AllowPrivateAccess = true, BindWidget))
	UBorder* Border;
	UPROPERTY(Meta = (AllowPrivateAccess = true, BindWidget))
	USizeBox* SizeBox;
	UPROPERTY(Meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* SlotNameTextBlock;

	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = true))
	float Width;
	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = true))
	float Height;
	UPROPERTY(EditInstanceOnly, Meta = (AllowPrivateAccess = true))
	FText SlotName;
};