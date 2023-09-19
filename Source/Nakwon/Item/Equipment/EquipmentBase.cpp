// Fill out your copyright notice in the Description page of Project Settings.


#include "../Equipment/EquipmentBase.h"

void AEquipmentBase::CreateInstance()
{
	Super::CreateInstance();
	
	ItemInstance.IntMap.Emplace(TEXT("CurrentDurability"), EquipmentInfo.MaxDurability);
}