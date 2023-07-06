// Fill out your copyright notice in the Description page of Project Settings.


#include "../GameAbilitySystem/MyAssetManager.h"
#include "AbilitySystemGlobals.h"

void UMyAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	UAbilitySystemGlobals::Get().InitGlobalData();
	UE_LOG(LogTemp, Warning, TEXT("Hello World!"));
}