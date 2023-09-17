// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Nakwon.h"
#include "GameFramework/HUD.h"
#include "BattleHUD.generated.h"

/**
 * 
 */
class UInGameMenuWidget;
class UInteractWidget;

// Weapon Modify Test
class UMaterialInstanceDynamic;
UCLASS()
class NAKWON_API ABattleHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	// Interact Widget
	FText GetSelectInteractText() const;
	void ShowInteractMenu(const TArray<FText>& MenuTextArray, FText InteractActorName = FText());
	void HideItemMenu();
	void SelectMenu(float WheelValue);

	// InGameMenu Widget
	void ToggleInGameMenu();

	// Weapon Modify Test
	void SetRenderTarget(UMaterialInstanceDynamic* NewMaterial);
protected:
	virtual void BeginPlay() override;

private:
	// Interact Widget
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = true))
	TSubclassOf<UInteractWidget> InteractWidgetClass;
	UInteractWidget* InteractWidget;

	// InGameMenu Widget
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = true))
	TSubclassOf<UInGameMenuWidget> InGameMenuWidgetClass;
	UInGameMenuWidget* InGameMenuWidget;
};