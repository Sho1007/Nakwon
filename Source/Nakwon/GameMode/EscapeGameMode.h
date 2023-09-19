// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EscapeGameMode.generated.h"

/**
 * 
 */
class AWayout;
class AMyCharacter;
UCLASS()
class NAKWON_API AEscapeGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	void SetSpawnPoint(AMyCharacter* Character);

private:
	TArray<AWayout*> WayoutArray;
};