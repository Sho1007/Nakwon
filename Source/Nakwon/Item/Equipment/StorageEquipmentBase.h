// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EquipmentBase.h"
#include "StorageEquipmentBase.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FOccupiedArray
{
	GENERATED_BODY()
	public:
	FOccupiedArray(int Length = 1)
	{
		Occupied.Init(false, Length);
	}

	UPROPERTY(EditAnywhere)
	TArray<bool> Occupied;
};

USTRUCT(BlueprintType)
struct FStorage
{
	GENERATED_BODY()

	public:
	FStorage(FIntPoint NewSize = { 3,3 }) : Size(NewSize)
	{
		OccupiedArray.Init(FOccupiedArray(Size.X), Size.Y);
	}

private:
	bool CanPutItemAt(const FIntPoint& At, const FIntPoint& ItemSize)
	{
		UE_LOG(LogTemp, Warning, TEXT("FStorage::CanPutItemAt : At : %s"), *At.ToString());
		if (At.Y + ItemSize.Y > Size.Y || At.X + ItemSize.X > Size.X)
		{
			UE_LOG(LogTemp, Warning, TEXT("FStorage::CanPutItemAt : Too Big Than Storage Size"));
			return false;
		}
		for (int i = At.Y; i < At.Y + ItemSize.Y; ++i)
		{
			for (int j = At.X; j < At.X + ItemSize.X; ++j)
			{
				if (OccupiedArray[i].Occupied[j] == true) return false;
			}
		}

		return true;
	}
	void FillSpace(const FIntPoint& At, const FIntPoint& ItemSize)
	{
		for (int i = At.Y; i < At.Y + ItemSize.Y; ++i)
		{
			for (int j = At.X; j < At.X + ItemSize.X; ++j)
			{
				OccupiedArray[i].Occupied[j] = true;
			}
		}
	}

public:
	bool PutItemToStorage(AItemBase* TargetItem)
	{
		if (TargetItem == nullptr) return false;

		bool bShouldRotate;
		return CheckEmptySpace(true, TargetItem, bShouldRotate).X != -1;
	}
	FIntPoint CheckEmptySpace(bool bPutItem, AItemBase* TargetItem, bool& bShouldRotate)
	{
		if (TargetItem == nullptr) return { -1, -1 };
		FIntPoint ItemSize = TargetItem->GetSize();
		for (int i = 0; i < Size.Y; ++i)
		{
			for (int j = 0; j < Size.X; ++j)
			{
				UE_LOG(LogTemp, Warning, TEXT("FStorage::CheckEmptySpace : X : %d, Y : %d"), j, i);
				if (OccupiedArray[i].Occupied[j] == true) continue;
				if (CanPutItemAt({ j, i }, ItemSize))
				{
					if (bPutItem)
					{
						ItemArray.Emplace(TargetItem->GetItemInstance());
						ItemArray.Last().StoragePosition = { j, i };
						FillSpace({ j, i }, ItemSize);
						TargetItem->Destroy();
					}

					return { j, i };
				}
				else if (CanPutItemAt({ j, i }, { ItemSize.Y, ItemSize.X }))
				{
					bShouldRotate = true;

					if (bPutItem)
					{
						TargetItem->Rotate();
						ItemArray.Emplace(TargetItem->GetItemInstance());
						ItemArray.Last().StoragePosition = { j, i };
						FillSpace({ j, i }, TargetItem->GetItemInfo().Size);
						TargetItem->Destroy();
					}

					return { j, i };
				}
			}
		}

		return { -1, -1 };
	}

	UPROPERTY(EditAnywhere)
	FIntPoint Size;
	UPROPERTY(EditAnywhere)
	TArray<FOccupiedArray> OccupiedArray;
	UPROPERTY(EditAnywhere)
	TArray<FItemInstance> ItemArray;
};

UCLASS()
class NAKWON_API AStorageEquipmentBase : public AEquipmentBase
{
	GENERATED_BODY()
	
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	bool PutItem(AItemBase* TargetItem);
private:
	UPROPERTY(Replicated, Meta = (AllowPrivateAccess))
	TArray<FStorage> Storage;
};