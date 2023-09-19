// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EscapeWidget.generated.h"

/**
 * 
 */
class UInGameMenuWidget;
class UInteractWidget;
class UEscapeProgressWidget;
UCLASS()
class NAKWON_API UEscapeWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Init();

	// Interact
	FText GetSelectInteractText() const;
	void ShowInteractMenu(const TArray<FText>& MenuTextArray, FText InteractActorName);
	void HideItemMenu();
	void SelectMenu();

	// InGameMenu
	void ToggleInGameMenu();

	// EscapeProgress
	void ShowEscapeProgress();
	void HideEscapeProgress();

	// Weapon Modify Test
	void SetRenderTarget(UMaterialInstanceDynamic* NewMaterial);
	
private:
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UInteractWidget* InteractWidget;
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UInGameMenuWidget* InGameMenuWidget;
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UEscapeProgressWidget* EscapeProgressWidget;
};
