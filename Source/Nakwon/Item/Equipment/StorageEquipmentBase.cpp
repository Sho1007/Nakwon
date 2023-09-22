// Fill out your copyright notice in the Description page of Project Settings.


#include "../Equipment/StorageEquipmentBase.h"
#include <Net/UnrealNetwork.h>

void AStorageEquipmentBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AStorageEquipmentBase, Storage);
}

bool AStorageEquipmentBase::PutItem(AItemBase* TargetItem)
{
	for (int i = 0; i < Storage.Num(); ++i)
	{
		if (Storage[i].PutItemToStorage(TargetItem)) return true;
	}
	return false;
}