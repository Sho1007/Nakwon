// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ItemBase.h"
#include "EquipmentBase.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FEquipmentInfo : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	EEquipmentType EquipmentType;
	UPROPERTY(EditDefaultsOnly)
	uint32 MaxDurability;
};

USTRUCT(BlueprintType)
struct FEquipmentInstance : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	uint32 CurrentDurability;
};

UCLASS()
class NAKWON_API AEquipmentBase : public AItemBase
{
	GENERATED_BODY()
	
public:
	virtual void LoadData(FItemInfo* ItemInfo, FItemInstance* ItemInstance);

protected:
	UPROPERTY(EditDefaultsOnly)
	EEquipmentType EquipmentType;
};
