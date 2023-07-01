// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../Nakwon.h"
#include "Blueprint/UserWidget.h"
#include "InteractWidget.generated.h"

/**
 * 
 */
class UImage;
class UTextBlock;
class UBorder;
class UVerticalBox;
class UInteractMenuSlotWidget;
UCLASS()
class NAKWON_API UInteractWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void InitWidget();
	void ShowInteractMenu(const TArray<FText>& MenuTextArray, FText InteractActorName = FText());
	void HideInteractMenu();
	void SelectMenu(float WheelValue);

	FText GetSelectInteractText() const;
private:
	void ActiveFirstMenu();
private:

	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = true))
	TSubclassOf<UInteractMenuSlotWidget> InteractMenuSlotWidgetClass;
	int32 FocusMenuNum;

	UPROPERTY(Meta = (AllowPrivateAccess = true, BindWidget))
	UImage* Img_CrossHair;
	UPROPERTY(Meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* TB_ItemName;
	UPROPERTY(Meta = (AllowPrivateAccess = true, BindWidget))
	UBorder* Brd_Menu;
	UPROPERTY(Meta = (AllowPrivateAccess = true, BindWidget))
	UVerticalBox* VB_Menu;
};