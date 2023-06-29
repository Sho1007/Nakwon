// Fill out your copyright notice in the Description page of Project Settings.


#include "../GameInstance/MyGameInstance.h"
#include "Engine/DataTable.h"
#include "../Item/ItemBase.h"

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
