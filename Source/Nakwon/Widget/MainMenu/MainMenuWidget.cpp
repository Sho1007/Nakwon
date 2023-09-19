// Fill out your copyright notice in the Description page of Project Settings.


#include "../MainMenu/MainMenuWidget.h"

#include <Components/Button.h>

bool UMainMenuWidget::Initialize()
{
    if (Super::Initialize() == false) return false;

    HostButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnHostButtonClicked);
    JoinButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnJoinButtonClicked);
    return true;
}

void UMainMenuWidget::OnHostButtonClicked()
{
    UE_LOG(LogTemp, Warning, TEXT("UMainMenuWidget::OnHostButtonClicked"));

    GetWorld()->ServerTravel(TEXT("/Game/Levels/L_Laboratory?listen"), true);
}

void UMainMenuWidget::OnJoinButtonClicked()
{
    UE_LOG(LogTemp, Warning, TEXT("UMainMenuWidget::OnJoinButtonClicked"));
    GetOwningPlayer()->ClientTravel(TEXT("127.0.0.1"), ETravelType::TRAVEL_Absolute);
}