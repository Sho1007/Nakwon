// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemPannelWidget.generated.h"

/**
 * 
 */
class UTextBlock;
class UImage;
class UHorizontalBox;
class AItemBase;
UCLASS()
class NAKWON_API UItemPannelWidget : public UUserWidget
{
	GENERATED_BODY()
	
	
	void InitWidget(AItemBase* TargetItem);
	
private:
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UHorizontalBox* DurabilityHorizontalBox;
	
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UImage* BackgroundImage;
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UImage* ItemImage;
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UImage* NotWorkImage;
	
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UTextBlock* ItemName;
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UTextBlock* CurrentDurability;
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UTextBlock* MaxDurability;
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UTextBlock* SlashText;

};