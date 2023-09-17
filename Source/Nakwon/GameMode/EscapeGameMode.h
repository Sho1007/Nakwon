// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EscapeGameMode.generated.h"

/**
 * 
 */
class AMyCharacter;
UCLASS()
class NAKWON_API AEscapeGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	void SetSpawnPoint(AMyCharacter* Character);
};