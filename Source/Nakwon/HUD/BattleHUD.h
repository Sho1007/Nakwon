// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Nakwon.h"
#include "GameFramework/HUD.h"
#include "BattleHUD.generated.h"

/**
 * 
 */
class UInteractWidget;
UCLASS()
class NAKWON_API ABattleHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	void ShowItemMenu(FName ItemName);
	void HideItemMenu();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = true))
	TSubclassOf<UInteractWidget> InteractWidgetClass;
	UInteractWidget* InteractWidget;
};