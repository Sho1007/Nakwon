// Fill out your copyright notice in the Description page of Project Settings.


#include "../Actor/Wayout.h"

#include "../Character/MyCharacter.h"

const TArray<AWayout*>& AWayout::GetDestinationArray() const
{
	return DestinationArray;
}

void AWayout::EnterPlayer(AMyCharacter* EnteredPlayer)
{
	Super::EnterPlayer(EnteredPlayer);
	EnteredPlayer->Escape(this, 5.0f);
}

void AWayout::LeavePlayer(AMyCharacter* LeavedPlayer)
{
	Super::LeavePlayer(LeavedPlayer);
	LeavedPlayer->StopEscape(this);
}