// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponPartsBase.h"
#include "ModdableWeaponPartsBase.generated.h"

/**
 * 
 */
UCLASS()
class NAKWON_API AModdableWeaponPartsBase : public AWeaponPartsBase
{
	GENERATED_BODY()
	
public:
	bool EquipWeaponParts(int32 SlotIndex, AWeaponPartsBase* WeaponParts);
	bool CheckIsEquipable(int32 SlotIndex, EWeaponPartsType NewWeaponPartsType);

protected:
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = true))
	TArray<FWeaponPartsSlot> WeaponPartsSlotArray;
};