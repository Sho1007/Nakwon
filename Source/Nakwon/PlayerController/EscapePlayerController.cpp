// Fill out your copyright notice in the Description page of Project Settings.


#include "../PlayerController/EscapePlayerController.h"

#include "../GameMode/EscapeGameMode.h"
#include "../Character/MyCharacter.h"
#include "../Item/ItemBase.h"

#include "../Widget/Escape/EscapeWidget.h"

void AEscapePlayerController::SetSpawnPoint_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("AEscapePlayerController::SetSpawnPoint"));
	if (AEscapeGameMode* GameMode = GetWorld()->GetAuthGameMode<AEscapeGameMode>())
	{
		if (AMyCharacter* PlayerCharacter = GetPawn<AMyCharacter>())
		{
			GameMode->SetSpawnPoint(PlayerCharacter);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("AEscapePlayerController::SetSpawnPoint : Invalid Pawn Class"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AEscapePlayerController::SetSpawnPoint : GameMode is Null"));
	}
}

void AEscapePlayerController::ShowEscapeProgress_Implementation()
{
	EscapeWidget->ShowEscapeProgress();
}

void AEscapePlayerController::HideEscapeProgress_Implementation()
{
	EscapeWidget->HideEscapeProgress();
}

void AEscapePlayerController::ShowInteractMenu()
{
	UE_LOG(LogTemp, Warning, TEXT("AEscapePlayerController::ShowInteractMenu"));

	if (AMyCharacter* MyCharacter = GetPawn<AMyCharacter>())
	{
		UE_LOG(LogTemp, Warning, TEXT("AEscapePlayerController::ShowInteractMenu : Check Character"));
		EscapeWidget->ShowInteractMenu(MyCharacter->GetMenuTextArray(), FText::FromName(TEXT("Test Name")));
		if (AItemBase* Item = Cast<AItemBase>(MyCharacter->GetInteractActor()))
		{
			UE_LOG(LogTemp, Warning, TEXT("AEscapePlayerController::ShowInteractMenu : Check Item"));
			// EscapeWidget->ShowInteractMenu(MyCharacter->GetMenuTextArray(), Item->GetItemName());
		}
	}
}

void AEscapePlayerController::HideInteractMenu()
{
	if (EscapeWidget) EscapeWidget->HideItemMenu();
}

void AEscapePlayerController::SelectMenu()
{
	EscapeWidget->SelectMenu();
}

FText AEscapePlayerController::GetSelectedInteractText()
{
	return EscapeWidget->GetSelectInteractText();
}

void AEscapePlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController() == false) return;

	UE_LOG(LogTemp, Warning, TEXT("AEscapePlayerController::BeginPlay"));
	check(EscapeWidgetClass);
	EscapeWidget = CreateWidget<UEscapeWidget>(this, EscapeWidgetClass, TEXT("EscapeWidget"));
	EscapeWidget->AddToViewport();
	EscapeWidget->Init();

	SetInputMode(FInputModeGameOnly());
	SetShowMouseCursor(false);
}