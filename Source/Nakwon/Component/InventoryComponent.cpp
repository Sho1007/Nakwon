// Fill out your copyright notice in the Description page of Project Settings.


#include "../Component/InventoryComponent.h"

#include "Net/UnrealNetwork.h"

#include "../GameInstance/MyGameInstance.h"

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
	//if (FItemInfo* ItemInfo = GetWorld()->GetGameInstance<UMyGameInstance>()->FindItemInfo(NewItemRow))
	//{
	//	for (int i = 0; i < ItemArray.Num(); ++i)
	//	{
	//		if (ItemArray[i].ItemRow == NewItemRow)
	//		{ 
	//			if (ItemArray[i].IntMap[TEXT("CurrentStack")] + 1 <= ItemInfo->IntMap[TEXT("MaxStack")])
	//			{
	//				// Check Is Valid (Check Other Take That Item)
	//				if (IsValid(TargetItem)) TargetItem->Destroy();
	//				ItemArray[i].IntMap[TEXT("CurrentStack")]++;
	//				return;
	//			}
	//		}
	//	}
	//	ItemArray.Add(TargetItem->GetItemInstance());
	//	TargetItem->Destroy();
	//}
}

void UInventoryComponent::EquipItem_Implementation(AItemBase* TargetItem)
{
	FItemInstance ItemInstance = TargetItem->GetItemInstance();

	FName NewItemRow = TargetItem->GetItemRow();
	UE_LOG(LogTemp, Warning, TEXT("UInventoryComponent::TakeItem : %s"), *NewItemRow.ToString());
	if (FItemInfo* ItemInfo = GetWorld()->GetGameInstance<UMyGameInstance>()->FindItemInfo(NewItemRow))
	{
	}
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void UInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UInventoryComponent, ItemArray);
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}