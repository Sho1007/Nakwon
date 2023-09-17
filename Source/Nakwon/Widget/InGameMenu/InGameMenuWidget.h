// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameMenuWidget.generated.h"

/**
 * 
 */
class UImage;

// Test : Weapon Modify
class UMaterialInstanceDynamic;

UCLASS()
class NAKWON_API UInGameMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetUp();

	void Toggle();

	void SetRenderTarget(UMaterialInstanceDynamic* NewMaterial);
private:
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UImage* Image_WeaponModifyTest;
};
