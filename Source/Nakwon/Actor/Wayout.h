// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Zone.h"
#include "Wayout.generated.h"

/**
 * 
 */
class AMyCharacter;
UCLASS()
class NAKWON_API AWayout : public AZone
{
	GENERATED_BODY()
	
public:
	const TArray<AWayout*>& GetDestinationArray() const;

	int GetPlayerCount() const;
	bool IsSpawnable() const;

	void SetSpawnPoint(AMyCharacter* Character);
private:
	virtual void EnterPlayer(AMyCharacter* EnteredPlayer);
	virtual void LeavePlayer(AMyCharacter* LeavedPlayer);
private:
	UPROPERTY(EditInstanceOnly, Meta = (AllowPrivateAccess))
	TArray<AWayout*> DestinationArray;
	UPROPERTY(EditInstanceOnly, Meta = (AllowPrivateAccess))
	float EscapeTime = 5.0f;
	UPROPERTY(EditInstanceOnly, Meta = (AllowPrivateAccess))
	int PlayerCount = 0;
	UPROPERTY(EditInstanceOnly, Meta = (AllowPrivateAccess, MakeEditWidget))
	TArray<FTransform> SpawnPointArray;
};