// Fill out your copyright notice in the Description page of Project Settings.


#include "../Escape/EscapeProgressWidget.h"

#include <Components/TextBlock.h>

#include "../../Character/MyCharacter.h"

void UEscapeProgressWidget::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("UEscapeProgressWidget::Init"));
	if (AMyCharacter* Character = GetOwningPlayerPawn<AMyCharacter>())
	{
		Character->EscapeTimeDelegate.BindUFunction(this, FName("UpdateEscapeTime"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UEscapeProgressWidget::Init : Character is Invalid"));
	}
}

void UEscapeProgressWidget::UpdateEscapeTime(float NewEscapeTime)
{
	EscapeTimeText->SetText(FText::FromString(FString::Printf(TEXT("%f"), NewEscapeTime)));
}