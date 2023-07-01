// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"


UENUM(BlueprintType)
enum class EItemAct : uint8
{
	NONE,
	Equip,
	USE,
	TAKE,
	EXAMINE,
	SIZE,
};

class UTexture2D;
UENUM(BlueprintType)
enum class EItemType : uint8
{
	NONE,
	EQUIPMENT,
	CONSUMABLE,
	INGREDIENT,
	QUEST,
	SIZE,
};