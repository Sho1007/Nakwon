// Fill out your copyright notice in the Description page of Project Settings.


#include "../GameInstance/MyGameInstance.h"

#include <Engine/DataTable.h>
#include <Kismet/GameplayStatics.h>

#include "../SaveGame/MySaveGame.h"
#include "../Item/ItemBase.h"
#include "../Item/Equipment/EquipmentBase.h"

FItemInfo* UMyGameInstance::FindItemInfo(FName ItemName)
{
    if (ItemInfoDataTable)
    {
        return ItemInfoDataTable->FindRow<FItemInfo>(ItemName, FString(""));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("ItemInfoDataTable is NULL"));
    }
    return nullptr;
}

FItemInstance* UMyGameInstance::FindItemInstance(FName Guid)
{
	if (ItemInstanceDataTable)
	{
		return ItemInstanceDataTable->FindRow<FItemInstance>(Guid, FString(""));
	}

	UE_LOG(LogTemp, Error, TEXT("UMyGameInstance::FindItemInstance : ItemInstanceDataTable is NULL"));
	return nullptr;
}

FEquipmentInfo* UMyGameInstance::FindEquipmentInfo(FName ItemName)
{
	if (EquipmentInfoDataTable)
	{
		return EquipmentInfoDataTable->FindRow<FEquipmentInfo>(ItemName, FString(""));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("EquipmentInfoDataTable is NULL"));
	}
	return nullptr;
}

void UMyGameInstance::LoadGameAsync()
{
	FAsyncLoadGameFromSlotDelegate LoadedDelegate;

	LoadedDelegate.BindUObject(this, &UMyGameInstance::OnLoadGameComplete);
	UGameplayStatics::AsyncLoadGameFromSlot(SLOT_NAME, 0, LoadedDelegate);
}

void UMyGameInstance::CreateSaveGame()
{
	SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	if (SaveGameInstance == nullptr || !IsValid(SaveGameInstance))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to Create Save Game : UMyGameInstance::CreateSaveGame"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UMyGameInstance::CreateSaveGame : Successed to Create Save Game"));
	}
}

void UMyGameInstance::OnLoadGameComplete(const FString& SlotName, const int32 UserIndex, USaveGame* SaveGameObject)
{
	if (SaveGameObject != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UMyGameInstance::OnLoadGameComplete : Load Successed"));

		// Save the Save Game Object to GameInstance;

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UMyGameInstance::OnLoadGameComplete : Load Failed"));

		// Create New Save Game Object And Save to GameInstance;
		CreateSaveGame();
	}
}