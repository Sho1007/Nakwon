// Fill out your copyright notice in the Description page of Project Settings.


#include "../Component/InventoryComponent.h"

#include <Net/UnrealNetwork.h>

#include "../Character/MyCharacter.h"
#include "../GameInstance/MyGameInstance.h"
#include "../Item/ItemBase.h"
#include "../Item/Equipment/StorageEquipmentBase.h"
#include "../Item/Equipment/Weapon/WeaponBase.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.

	PrimaryComponentTick.bCanEverTick = false;
	// ...


	EquipmentArray.Init(nullptr, (int32)EEquipmentSlotType::SIZE - 1);
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
	if (TargetEquipment == nullptr || SlotType == EEquipmentSlotType::SIZE) return;

	if (SlotType != EEquipmentSlotType::NONE)
	{
		// Slot을 정해서 장비할 경우 -> In DragDrop

		if (SlotType <= EEquipmentSlotType::EYEWEAR)
		{
			switch (SlotType)
			{
			case EEquipmentSlotType::EARPIECE:
				if (TargetEquipment->GetEquipmentInfo().EquipmentType != EEquipmentType::EARPIECE) return;
				break;
			case EEquipmentSlotType::HEADGEAR:
				if (TargetEquipment->GetEquipmentInfo().EquipmentType != EEquipmentType::HEADGEAR) return;
				if (EquipmentArray[(int32)EEquipmentSlotType::HEADGEAR] == nullptr)
				{
					EquipmentArray[(int32)EEquipmentSlotType::HEADGEAR] = TargetEquipment;
					EquipmentArray[(int32)EEquipmentSlotType::HEADGEAR]->SetEquipped(Cast<AMyCharacter>(GetOwner()), SlotType);
					/*TargetEquipment->AttachToComponent(Cast<AMyCharacter>(GetOwner())->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("headgear"));
					TargetEquipment->SetActorEnableCollision(false);*/
				}
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
			}
		}
		else if (SlotType <= EEquipmentSlotType::SCABBARD)
		{
			switch (SlotType)
			{
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
			}
		}
		else
		{
			AStorageEquipmentBase* StorageEquipment = Cast<AStorageEquipmentBase>(TargetEquipment);
			if (StorageEquipment == nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("UInventoryComponent::EquipItem : Invalid Equipment Type (Not StorageEquipment)"));
				return;
			}

			// Todo : 장비하게 된다면 -> 무게 증가, 만약 Inventory를 보고 있다면 업데이트, 추후 혹여나 Quest 까지 디벨롭이 된다면, QuestItem Check 후 Quest 상태 갱신
			// (Pouch Event 갱신 관련 이슈는 생각해보니, Check Quest Item이란 함수를 InGame 일때만 실행해주면 해결)
			switch (SlotType)
			{
			case EEquipmentSlotType::RIG:
				if (TargetEquipment->GetEquipmentInfo().EquipmentType != EEquipmentType::RIG) return;

				RigSlot = StorageEquipment;
				// PC->UpdateInventoryWidget(EEquipmentSlot::RIG);
				RigSlot->AttachToComponent(Cast<ACharacter>(GetOwner())->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("rig"));
				RigSlot->SetActorEnableCollision(false);
				break;
			case EEquipmentSlotType::BACKPACK:
				if (TargetEquipment->GetEquipmentInfo().EquipmentType != EEquipmentType::BACKPACK) return; // Slot에 바로 끌어다 놓을 경우를 대비해서 SlotType 비교
				
				BackpackSlot = StorageEquipment;
				// PC->UpdateInventoryWidget(EEquipmentSlot::BACKPACK);
				BackpackSlot->AttachToComponent(Cast<ACharacter>(GetOwner())->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("backpack"));
				BackpackSlot->SetActorEnableCollision(false);
				break;
			case EEquipmentSlotType::POUCH:
				if (PouchSlot || TargetEquipment->GetEquipmentInfo().EquipmentType != EEquipmentType::POUCH) return;
				// if (bIsInRaid) return;
				// PC->UpdateInventoryWidget(EEquipmentSlot::POUCH);
				PouchSlot = StorageEquipment;
				BackpackSlot->AttachToComponent(Cast<ACharacter>(GetOwner())->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
				PouchSlot->SetActorHiddenInGame(true);
				PouchSlot->SetActorEnableCollision(false);
				break;
			}
		}

	}
	else
	{
		// Slot이 정해지지 않은 경우 -> In World or In Inventory
		switch (TargetEquipment->GetEquipmentInfo().EquipmentType)
		{
		case EEquipmentType::EARPIECE:
			EquipItem(EEquipmentSlotType::EARPIECE, TargetEquipment);
			break;
		case EEquipmentType::HEADGEAR:
			EquipItem(EEquipmentSlotType::HEADGEAR, TargetEquipment);
			break;
		case EEquipmentType::FACECOVER:
			EquipItem(EEquipmentSlotType::FACECOVER, TargetEquipment);
			break;
		case EEquipmentType::ARMBAND:
			EquipItem(EEquipmentSlotType::ARMBAND, TargetEquipment);
			break;
		case EEquipmentType::BODYARMOR:
			EquipItem(EEquipmentSlotType::BODYARMOR, TargetEquipment);
			break;
		case EEquipmentType::EYEWEAR:
			EquipItem(EEquipmentSlotType::EYEWEAR, TargetEquipment);
			break;
		case EEquipmentType::WEAPON:
			if (AWeaponBase* TargetWeapon = Cast<AWeaponBase>(TargetEquipment))
			{
				//TargetWeapon->GetWeaponInfo();

				// Todo : WeaponType 검사 후 OnSling OnBack / 혹은 Holster / 혹은 Scabbard 에 장착 시도
				/*if (EquipmentArray[(int)EEquipmentSlotType::ONSLING] == nullptr)
			{

				EquipItem(EEquipmentSlotType::ONSLING, TargetEquipment);
			}
			else if ()
			{

			}*/
			}
			break;
		case EEquipmentType::RIG:
			EquipItem(EEquipmentSlotType::RIG, TargetEquipment);
			break;
		case EEquipmentType::BACKPACK:
			EquipItem(EEquipmentSlotType::BACKPACK, TargetEquipment);
			break;
		case EEquipmentType::POUCH:
			EquipItem(EEquipmentSlotType::POUCH, TargetEquipment);
			break;
		}
	}
	// Todo : Update Equipment Widget
	// PC->UpdateEquipmentWidget;
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner()->HasAuthority())
	{
		GetOwner()->SetReplicates(true);
		SetIsReplicated(true);
	}
}

void UInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UInventoryComponent, EquipmentArray);
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