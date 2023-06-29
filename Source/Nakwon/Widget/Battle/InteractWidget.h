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
UCLASS()
class NAKWON_API UInteractWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void InitWidget();
	void ShowItemMenu(FName ItemName);
	void HideItemMenu();

private:
	void ActiveFirstMenu();
private:
	UPROPERTY( Meta = (AllowPrivateAccess = true, BindWidget))
	UBorder* Brd_Menu;
	UPROPERTY(Meta = (AllowPrivateAccess = true, BindWidget))
	UBorder* Brd_Use;
	UPROPERTY(Meta = (AllowPrivateAccess = true, BindWidget))
	UBorder* Brd_Equip;
	UPROPERTY(Meta = (AllowPrivateAccess = true, BindWidget))
	UBorder* Brd_Take;
	UPROPERTY(Meta = (AllowPrivateAccess = true, BindWidget))
	UBorder* Brd_Examine;

	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = true))
	TArray<UBorder*> MenuArray;

	int32 ActiveMenu;

	UPROPERTY(Meta = (AllowPrivateAccess = true, BindWidget))
	UImage* Img_CrossHair;
	UPROPERTY(Meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* TB_ItemName;
};