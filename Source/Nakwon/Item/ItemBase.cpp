// Fill out your copyright notice in the Description page of Project Settings.


#include "../Item/ItemBase.h"

#include "../HUD/BattleHUD.h"
#include "../Character/MyCharacter.h"
#include "../Component/InventoryComponent.h"
#include "../GameInstance/MyGameInstance.h"

// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority())
	{
		SetReplicates(true);
	}
	Guid = FGuid::NewGuid();
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("GUID : %s"), *Guid.ToString()));
}

// Called every frame
void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AItemBase::Interact(AMyCharacter* InteractCharacter, FText InteractionName)
{
	UE_LOG(LogTemp, Warning, TEXT("AItemBase::Interact : %s"), *InteractionName.ToString());

	//if (InteractionName.CompareTo(ItemMenuArray[0]) == 0)
	//{
	//	//UE_LOG(LogTemp, Warning, TEXT("AItemBase::Interact Use"));
	//	UseItem();
	//}
	//else if (InteractionName.CompareTo(ItemMenuArray[1]) == 0)
	//{
	//	//UE_LOG(LogTemp, Warning, TEXT("AItemBase::Interact Take"));
	//	TakeItem(InteractCharacter);
	//}
	//else if (InteractionName.CompareTo(ItemMenuArray[2]) == 0)
	//{
	//	//UE_LOG(LogTemp, Warning, TEXT("AItemBase::Interact Examine"));
	//	ExamineItem();
	//}
}

void AItemBase::ShowInteractMenu()
{
	/*if (ABattleHUD* HUD = GetWorld()->GetFirstPlayerController()->GetHUD<ABattleHUD>())
	{
		if (FItemInfo* ItemInfo = GetGameInstance<UMyGameInstance>()->FindItemInfo(ItemInstance.ItemRow))
		{
			HUD->ShowInteractMenu(ItemMenuArray, ItemInfo->ItemName);
		}
	}*/
}

void AItemBase::LoadData(FItemInfo* ItemInfo, FItemInstance* ItemInstance)
{
	this->Guid = ItemInstance->Guid;
	this->CurrentStack = ItemInstance->CurrentStack;

	this->Name = ItemInfo->Name;
	this->Class = ItemInfo->Class;
	this->Type = ItemInfo->Type;
	this->Image = ItemInfo->Image;
	this->Width = ItemInfo->Width;
	this->Height = ItemInfo->Height;
	this->MaxStack = ItemInfo->MaxStack;
}

FName AItemBase::GetItemRow() const
{
	//return ItemInstance.ItemRow;
	return FName();
}

FItemInstance AItemBase::GetItemInstance() const
{
	//return ItemInstance;
	return FItemInstance();
}

void AItemBase::UseItem()
{
}

void AItemBase::TakeItem(AMyCharacter* InteractCharacter)
{
	if (UInventoryComponent* InventoryComponent = Cast<UInventoryComponent>(InteractCharacter->FindComponentByClass(UInventoryComponent::StaticClass())))
	{
		InventoryComponent->TakeItem(this);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AItemBase::TakeItem : Interact Character Has No Inventory Component"));
	}
}

void AItemBase::ExamineItem()
{
}