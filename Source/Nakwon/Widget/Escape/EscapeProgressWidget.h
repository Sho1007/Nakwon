// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EscapeProgressWidget.generated.h"

/**
 * 
 */
class UTextBlock;
UCLASS()
class NAKWON_API UEscapeProgressWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Init();
private:
	UFUNCTION()
	void UpdateEscapeTime(float NewEscapeTime);

private:
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UTextBlock* EscapeTimeText;
};