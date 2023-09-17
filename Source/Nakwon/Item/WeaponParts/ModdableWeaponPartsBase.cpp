// Fill out your copyright notice in the Description page of Project Settings.


#include "../WeaponParts/ModdableWeaponPartsBase.h"


bool AModdableWeaponPartsBase::EquipWeaponParts(int32 SlotIndex, AWeaponPartsBase* WeaponParts)
{
	if (SlotIndex < 0 || SlotIndex >= WeaponPartsSlotArray.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("AWeaponPartBase::EquipWeaponParts : Invalid Slot Index"));
		return false;
	}

	if (CheckIsEquipable(SlotIndex, WeaponParts->GetWeaponPartsType()) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AWeaponPartBase::EquipWeaponParts : Invalid WeaponPartsType"));
		return false;
	}

	if (WeaponPartsSlotArray[SlotIndex].WeaponParts != nullptr && WeaponPartsSlotArray[SlotIndex].WeaponParts->IsValidLowLevelFast())
	{
		// Todo : Change And Old One Move To Backpack (If backpack has empty space)
		UE_LOG(LogTemp, Error, TEXT("AWeaponPartBase::EquipWeaponParts : Slot Is Not Empty"));
		return false;
	}
	else
	{
		WeaponPartsSlotArray[SlotIndex].WeaponParts = WeaponParts;
		const TMap<FName, float>& NewStatus = WeaponParts->GetWeaponPartsStatus();
		for (auto Iter : NewStatus)
		{
			this->Status[Iter.Key] += Iter.Value;

			// Todo : Apply Status
		}
	}

	return true;
}

bool AModdableWeaponPartsBase::CheckIsEquipable(int32 SlotIndex, EWeaponPartsType NewWeaponPartsType)
{
	// CheckIsEquipable
	bool bIsEquipable = false;
	for (auto EquipableType : WeaponPartsSlotArray[SlotIndex].WeaponPartsTypeArray)
	{
		if (EquipableType == NewWeaponPartsType)
		{
			bIsEquipable = true;
			break;
		}
	}
	return bIsEquipable;
}