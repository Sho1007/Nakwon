// Fill out your copyright notice in the Description page of Project Settings.


#include "../Equipment/EquipmentBase.h"

#include <Net/UnrealNetwork.h>

#include "../../Character/MyCharacter.h"
#include "../../GameInstance/MyGameInstance.h"
#include "../../Component/InventoryComponent.h"

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

void AEquipmentBase::Interact(AMyCharacter* InteractCharacter, FText InteractionName)
{
	Super::Interact(InteractCharacter, InteractionName);

	if (InteractionName.CompareTo(FText::FromName(TEXT("Equip"))) == 0)
	{
		if (UInventoryComponent* InventoryComponent = Cast<UInventoryComponent>(InteractCharacter->GetComponentByClass(UInventoryComponent::StaticClass())))
		{
			InventoryComponent->EquipItem(EEquipmentSlotType::NONE, this);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("AEquipmentBase::Interact : Invalid Inventory Component"));
		}
	}
}

void AEquipmentBase::SetEquipped_Implementation(AMyCharacter* InteractCharacter, EEquipmentSlotType SlotType)
{
	if (InteractCharacter->HasAuthority())
	{
		SetOwner(InteractCharacter);
		// Todo : EquipmentSlotType 에 맞게 Socket Name 1대 1매칭 (배열?) 로 리턴
		//AttachToComponent(InteractCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, !!);
	}
	SetActorEnableCollision(false);
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