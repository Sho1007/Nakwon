// Fill out your copyright notice in the Description page of Project Settings.


#include "../Equipment/EquipmentBase.h"

#include <Net/UnrealNetwork.h>

#include "../../GameInstance/MyGameInstance.h"

void AEquipmentBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AEquipmentBase, EquipmentInstance);
}

void AEquipmentBase::Init()
{
}

void AEquipmentBase::LoadData(FItemInstance* NewItemInstance)
{
	Super::LoadData(NewItemInstance);
	EquipmentInstance = *GetGameInstance<UMyGameInstance>()->FindEquipmentInstance(FName(*ItemInstance.Guid.ToString()));
}

void AEquipmentBase::CreateInstance(bool bFromStore)
{
	Super::CreateInstance(bFromStore);

	if (bFromStore)
	{
		EquipmentInstance.CurrentDurability = EquipmentInfo.MaxDurability;
	}
	else
	{
		EquipmentInstance.CurrentDurability = FMath::RandRange(1, EquipmentInfo.MaxDurability);
	}
}

const FEquipmentInfo& AEquipmentBase::GetEquipmentInfo() const
{
	return EquipmentInfo;
}

const FEquipmentInstance& AEquipmentBase::GetEquipmentInstance() const
{
	return EquipmentInstance;
}

void AEquipmentBase::SetCurrentDurability(int NewCurrentDurability)
{
	EquipmentInstance.CurrentDurability = NewCurrentDurability;

	Delegate_CurrrentDurability.ExecuteIfBound(EquipmentInstance.CurrentDurability);
}

void AEquipmentBase::OnRep_EquipmentInstance()
{
	Delegate_CurrrentDurability.ExecuteIfBound(EquipmentInstance.CurrentDurability);
}