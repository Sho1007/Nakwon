// Fill out your copyright notice in the Description page of Project Settings.


#include "../PlayerState/BattlePlayerState.h"
#include "Net/UnrealNetwork.h"

bool ABattlePlayerState::IsKnowItem(FName ItemRow)
{
	return KnownItemArray.Find(ItemRow) != INDEX_NONE;
}

void ABattlePlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABattlePlayerState, KnownItemArray);
}