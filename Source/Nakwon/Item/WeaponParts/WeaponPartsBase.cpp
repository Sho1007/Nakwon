// Fill out your copyright notice in the Description page of Project Settings.


#include "../WeaponParts/WeaponPartsBase.h"

EWeaponPartsType AWeaponPartsBase::GetWeaponPartsType() const
{
	return WeaponPartsType;
}

const TMap<FName, float>& AWeaponPartsBase::GetWeaponPartsStatus() const
{
	return Status;
}