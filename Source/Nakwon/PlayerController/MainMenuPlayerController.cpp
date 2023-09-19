// Fill out your copyright notice in the Description page of Project Settings.


#include "../PlayerController/MainMenuPlayerController.h"

#include "../Widget/MainMenu/MainMenuWidget.h"

void AMainMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(MainMenuWidgetClass);
	MainMenuWidget = CreateWidget<UMainMenuWidget>(this, MainMenuWidgetClass, TEXT("MainMenuWidget"));
	MainMenuWidget->AddToViewport();

	SetInputMode(FInputModeUIOnly());
	SetShowMouseCursor(true);
}