// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Nakwon.h"
#include "GameFramework/HUD.h"
#include "BattleHUD.generated.h"

/**
 * 
 */
class UInteractWidget;
class UInteractMenuSlotWidget;
UCLASS()
class NAKWON_API ABattleHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	FText GetSelectInteractText() const;
	void ShowInteractMenu(const TArray<FText>& MenuTextArray, FText InteractActorName = FText());
	void HideItemMenu();
	void SelectMenu(float WheelValue);
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = true))
	TSubclassOf<UInteractWidget> InteractWidgetClass;
	UInteractWidget* InteractWidget;
};