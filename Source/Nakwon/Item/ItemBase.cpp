// Fill out your copyright notice in the Description page of Project Settings.


#include "../Item/ItemBase.h"

#include "../Character/MyCharacter.h"
#include "../PlayerController/EscapePlayerController.h"
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
	ItemInstance.Guid = FGuid::NewGuid();
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("GUID : %s"), *ItemInstance.Guid.ToString()));
}

// Called every frame
void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AItemBase::Interact(AMyCharacter* InteractCharacter, FText InteractionName)
{
	UE_LOG(LogTemp, Warning, TEXT("AItemBase::Interact : %s"), *InteractionName.ToString());

	if (InteractionName.CompareTo(FText::FromName(TEXT("Use"))) == 0)
	{
		
		UseItem();
	}
	else if (InteractionName.CompareTo(FText::FromName(TEXT("Take"))) == 0)
	{
		//UE_LOG(LogTemp, Warning, TEXT("AItemBase::Interact Take"));
		TakeItem(InteractCharacter);
	}
	else if (InteractionName.CompareTo(FText::FromName(TEXT("Examine"))) == 0)
	{
		//UE_LOG(LogTemp, Warning, TEXT("AItemBase::Interact Examine"));
		ExamineItem();
	}
}

void AItemBase::ShowInteractMenu(AMyCharacter* InteractCharacter)
{
	UE_LOG(LogTemp, Warning, TEXT("AItemBase::ShowInteractMenu"));
	if (AEscapePlayerController* PC = InteractCharacter->GetController<AEscapePlayerController>())
	{
		// Todo : If player Doesn't know this item, Add Exmaine
		TArray<FText> NewMenuTextArray;
		NewMenuTextArray.Add(FText::FromName(TEXT("Take")));
		if (InteractCharacter->CheckKnowItem(ItemInstance.ItemRow))
		{
			for (FText Text : MenuTextArray)
			{
				NewMenuTextArray.Add(Text);
			}
		}
		else
		{
			NewMenuTextArray.Add(FText::FromName(TEXT("Examine")));
		}
		
		InteractCharacter->SetMenuTextArray(NewMenuTextArray);

		if (PC->HasAuthority() && PC->IsLocalController()) PC->ShowInteractMenu();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AItemBase::ShowInteractMenu : Invalid PlayerController Class"));
	}
	/*if (ABattleHUD* HUD = GetWorld()->GetFirstPlayerController()->GetHUD<ABattleHUD>())
	{
		if (FItemInfo* ItemInfo = GetGameInstance<UMyGameInstance>()->FindItemInfo(ItemInstance.ItemRow))
		{
			HUD->ShowInteractMenu(ItemMenuArray, ItemInfo->ItemName);
		}
	}*/
}

void AItemBase::LoadData(FItemInstance* NewItemInstance)
{
	ItemInstance = *NewItemInstance;
}

void AItemBase::CreateInstance()
{
	ItemInstance.Guid = FGuid::NewGuid();
	ItemInstance.IntMap.Emplace(TEXT("CurrentStack"), 1);
}

FName AItemBase::GetItemRow() const
{
	return ItemInstance.ItemRow;
}

FItemInstance AItemBase::GetItemInstance() const
{
	return ItemInstance;
}

FText AItemBase::GetItemName() const
{
	return ItemInfo.Name;
}

void AItemBase::UseItem_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("AItemBase::UseItem : %s"), *this->GetName());
}

void AItemBase::TakeItem_Implementation(AMyCharacter* InteractCharacter)
{
	UE_LOG(LogTemp, Warning, TEXT("AItemBase::TakeItem : %s to %s"), *this->GetName(), *InteractCharacter->GetName());
	if (UInventoryComponent* InventoryComponent = Cast<UInventoryComponent>(InteractCharacter->FindComponentByClass(UInventoryComponent::StaticClass())))
	{
		InventoryComponent->TakeItem(this);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AItemBase::TakeItem : Interact Character Has No Inventory Component"));
	}
}

void AItemBase::ExamineItem_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("AItemBase::ExamineItem : %s"), *this->GetName());
}