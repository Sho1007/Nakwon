// Fill out your copyright notice in the Description page of Project Settings.


#include "../GameMode/MainMenuGameMode.h"

#include <Kismet/GameplayStatics.h>

#include "../GameInstance/MyGameInstance.h"

void AMainMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	GetGameInstance<UMyGameInstance>()->LoadGameAsync();
}