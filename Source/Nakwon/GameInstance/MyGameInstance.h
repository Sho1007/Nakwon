// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Nakwon.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
class UDataTable;

struct FItemInfo;
UCLASS()
class NAKWON_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	FItemInfo* FindItemInfo(FName ItemName);
private:
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = true))
	UDataTable* ItemInfoDataTable;
};