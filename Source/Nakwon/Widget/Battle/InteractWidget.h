// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractWidget.generated.h"

/**
 * 
 */
class UImage;
UCLASS()
class NAKWON_API UInteractWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void InitWidget();

private:
	UPROPERTY(Meta = (AllowPrivateAccess = true, BindWidget))
	UImage* Img_CrossHair;
};
