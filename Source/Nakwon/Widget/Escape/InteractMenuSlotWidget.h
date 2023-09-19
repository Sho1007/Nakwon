// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../Nakwon.h"
#include "Blueprint/UserWidget.h"
#include "InteractMenuSlotWidget.generated.h"

/**
 * 
 */
class UTextBlock;
class UBorder;
UCLASS()
class NAKWON_API UInteractMenuSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Getter / Setter
	FText GetText() const;
	void SetText(const FText& NewText);

	void SetFocus(bool bIsFocused);
	
private:
	UPROPERTY(Meta = (AllowPrivateAccess = true, BindWidget))
	UBorder* Brd_Slot;
	UPROPERTY(Meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* TB_Slot;
};
