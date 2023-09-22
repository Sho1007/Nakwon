// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class AbilityID : uint8
{
	None UMETA(DisplayName = "None"),
	Confirm UMETA(DisplayName = "Confirm"),
	Cancel UMETA(DisplayName = "Cancel")

};

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
	WEAPONPARTS,
	SIZE,
};

UENUM(BlueprintType)
enum class EEquipmentType : uint8
{
	NONE,
	EARPIECE,
	HEADGEAR,
	FACECOVER,
	ARMBAND,
	BODYARMOR,
	EYEWEAR,
	WEAPON,
	RIG,
	BACKPACK,
	POUCH,
	SIZE                                                 
};

UENUM(BlueprintType)
enum class EEquipmentSlotType : uint8
{
	NONE,
	EARPIECE,
	HEADGEAR,
	FACECOVER,
	ARMBAND,
	BODYARMOR,
	EYEWEAR,
	ONSLING,
	ONBACK,
	HOLSTER,
	SCABBARD,
	RIG,
	BACKPACK,
	POUCH,
	SIZE
};