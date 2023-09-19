// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EscapePlayerController.generated.h"

/**
 * 
 */
class UEscapeWidget;
UCLASS()
class NAKWON_API AEscapePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	UFUNCTION(Server, Reliable)
	void SetSpawnPoint();
	void SetSpawnPoint_Implementation();


	// Widget
	UFUNCTION(Client, Reliable)
	void ShowEscapeProgress();
	void ShowEscapeProgress_Implementation();
	
	UFUNCTION(Client, Reliable)
	void HideEscapeProgress();
	void HideEscapeProgress_Implementation();

	void ShowInteractMenu();
	void HideInteractMenu();
	
	void SelectMenu();
	
	FText GetSelectedInteractText();

private:
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess))
	TSubclassOf<UEscapeWidget> EscapeWidgetClass;
	UEscapeWidget* EscapeWidget;
};