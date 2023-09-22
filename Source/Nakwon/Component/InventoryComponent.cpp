// Fill out your copyright notice in the Description page of Project Settings.


#include "../Component/InventoryComponent.h"

#include <Net/UnrealNetwork.h>

#include "../GameInstance/MyGameInstance.h"
#include "../Item/ItemBase.h"
#include "../Item/Equipment/StorageEquipmentBase.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UInventoryComponent::TakeItem_Implementation(AItemBase* TargetItem)
{
	FName NewItemRow = TargetItem->GetItemRow();
	UE_LOG(LogTemp, Warning, TEXT("UInventoryComponent::TakeItem : %s"), *NewItemRow.ToString());

	// Check Empty Space

	EquipmentArray;

	if (RigSlot && RigSlot->PutItem(TargetItem))
	{
		UE_LOG(LogTemp, Warning, TEXT("UInventoryComponent::TakeItem : Successed to Put Item into Rig Storage"));
		return;
	}
	else if (PocketSlot && PocketSlot->PutItem(TargetItem))
	{
		UE_LOG(LogTemp, Warning, TEXT("UInventoryComponent::TakeItem : Successed to Put Item into Pocket Storage"));
		return;
	}
	else if (BackpackSlot && BackpackSlot->PutItem(TargetItem))
	{
		UE_LOG(LogTemp, Warning, TEXT("UInventoryComponent::TakeItem : Successed to Put Item into Backpack Storage"));
		return;
	}
	else if (PouchSlot && PouchSlot->PutItem(TargetItem))
	{
		UE_LOG(LogTemp, Warning, TEXT("UInventoryComponent::TakeItem : Successed to Put Item into Pouch Storage"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("UInventoryComponent::TakeItem : Failed to Put Item into Storage"));
}

void UInventoryComponent::EquipItem_Implementation(EEquipmentSlotType SlotType, AEquipmentBase* TargetEquipment)
{
	// 1. 칸이 비어 있는 경우
	// 2. 칸이 다른 장비로 차 있는 경우
	//	1. 다른 장비를 다시 가방에 넣고
	//	2. 해당 칸을 장비로 교체
	switch (SlotType)
	{
	case EEquipmentSlotType::EARPIECE:
		if (TargetEquipment->GetEquipmentInfo().EquipmentType != EEquipmentType::EARPIECE) return;
		break;
	case EEquipmentSlotType::HEADGEAR:
		if (TargetEquipment->GetEquipmentInfo().EquipmentType != EEquipmentType::HEADGEAR) return;
		break;
	case EEquipmentSlotType::FACECOVER:
		if (TargetEquipment->GetEquipmentInfo().EquipmentType != EEquipmentType::FACECOVER) return;
		break;
	case EEquipmentSlotType::ARMBAND:
		if (TargetEquipment->GetEquipmentInfo().EquipmentType != EEquipmentType::ARMBAND) return;
		break;
	case EEquipmentSlotType::BODYARMOR:
		if (TargetEquipment->GetEquipmentInfo().EquipmentType != EEquipmentType::BODYARMOR) return;
		break;
	case EEquipmentSlotType::EYEWEAR:
		if (TargetEquipment->GetEquipmentInfo().EquipmentType != EEquipmentType::EYEWEAR) return;
		break;
	case EEquipmentSlotType::ONSLING:
		if (TargetEquipment->GetEquipmentInfo().EquipmentType != EEquipmentType::WEAPON) return;
		// Todo : WeaponType Check
		break;
	case EEquipmentSlotType::ONBACK:
		if (TargetEquipment->GetEquipmentInfo().EquipmentType != EEquipmentType::WEAPON) return;
		// Todo : WeaponType Check
		break;
	case EEquipmentSlotType::HOLSTER:
		if (TargetEquipment->GetEquipmentInfo().EquipmentType != EEquipmentType::WEAPON) return;
		// Todo : WeaponType Check
		break;
	case EEquipmentSlotType::SCABBARD:
		if (TargetEquipment->GetEquipmentInfo().EquipmentType != EEquipmentType::WEAPON) return;
		// Todo : WeaponType Check
		break;
	case EEquipmentSlotType::RIG:
		if (TargetEquipment->GetEquipmentInfo().EquipmentType != EEquipmentType::RIG) return;
		break;
	case EEquipmentSlotType::BACKPACK:
		if (TargetEquipment->GetEquipmentInfo().EquipmentType != EEquipmentType::BACKPACK) return;
		break;
	case EEquipmentSlotType::POUCH:
		if (PouchSlot || TargetEquipment->GetEquipmentInfo().EquipmentType != EEquipmentType::POUCH) return;
		PouchSlot = Cast<AStorageEquipmentBase>(TargetEquipment);
		break;
	}

	// Todo : Update Equipment Widget
	// PC->UpdateEquipmentWidget;
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	DOREPLIFETIME(UInventoryComponent, RigSlot);
	DOREPLIFETIME(UInventoryComponent, PocketSlot);
	DOREPLIFETIME(UInventoryComponent, BackpackSlot);
	DOREPLIFETIME(UInventoryComponent, PouchSlot);
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}