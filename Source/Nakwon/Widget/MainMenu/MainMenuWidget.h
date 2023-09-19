// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
class UButton;
UCLASS()
class NAKWON_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;
private:
	UFUNCTION()
	void OnHostButtonClicked();
	UFUNCTION()
	void OnJoinButtonClicked();
private:
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UButton* HostButton;
	UPROPERTY(Meta = (AllowPrivateAccess, BindWidget))
	UButton* JoinButton;
};