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
	if (FItemInfo* ItemInfo = GetWorld()->GetGameInstance<UMyGameInstance>()->FindItemInfo(NewItemRow))
	{
		bool isAdded = false;
		for (int i = 0; i < ItemArray.Num(); ++i)
		{
			if (ItemArray[i].ItemRow == NewItemRow)
			{
				if (ItemArray[i].CurrentStack + 1 <= ItemInfo->MaxStack)
				{
					ItemArray[i].CurrentStack++;
					return;
				}
			}
		}

		ItemArray.Add(FItemInstance(NewItemRow, 1));
		TargetItem->Destroy();
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