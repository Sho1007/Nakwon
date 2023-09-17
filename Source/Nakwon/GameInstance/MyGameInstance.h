// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Nakwon.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
class UDataTable;
class USaveGame;
class UMySaveGame;

struct FItemInfo;
struct FItemInstance;
struct FEquipmentInfo;
struct FEquipmentInstance;
UCLASS()
class NAKWON_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	// DataTable
	FItemInfo* FindItemInfo(FName ItemName);
	FItemInstance* FindItemInstance(FName Guid);
	
	FEquipmentInfo* FindEquipmentInfo(FName ItemName);
	FEquipmentInstance* FindEquipmentInstance(FName Guid);

	// SaveGame
	void LoadGameAsync();

private:
	// SaveGame
	void CreateSaveGame();
	UFUNCTION()
	void OnLoadGameComplete(const FString& SlotName, const int32 UserIndex, USaveGame* SaveGameObject);

private:
	// SaveGame
	const FString SLOT_NAME = "SaveSlot";
	UMySaveGame* SaveGameInstance = nullptr;

	// DataTable
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = true))
	UDataTable* ItemInfoDataTable;
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = true))
	UDataTable* ItemInstanceDataTable;
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = true))
	UDataTable* EquipmentInfoDataTable;
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = true))
	UDataTable* EquipmentInstanceDataTable;
};