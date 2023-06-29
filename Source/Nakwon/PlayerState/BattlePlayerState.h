// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Nakwon.h"
#include "GameFramework/PlayerState.h"
#include "BattlePlayerState.generated.h"

/**
 * 
 */
UCLASS()
class NAKWON_API ABattlePlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	bool IsKnowItem(FName ItemRow);
protected:
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;
private:
	UPROPERTY(Replicated, Meta = (AllowPrivateAccess = true))
	TArray<FName> KnownItemArray;
};