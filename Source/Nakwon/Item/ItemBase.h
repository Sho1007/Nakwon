// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Nakwon.h"
#include "GameFramework/Actor.h"

#include <Engine/DataTable.h>
#include <Misc/Guid.h>
#include "../Interface/InteractInterface.h"

#include "ItemBase.generated.h"

// Inventory에 존재하면, 표현하기 위한 구조체
class AItemBase;
USTRUCT(BlueprintType)
struct FItemInfo : public FTableRowBase
{
	GENERATED_BODY()
public:
	FItemInfo()
		: Name(FText()), Class(nullptr), Type(EItemType::NONE), Image(nullptr)
	{
	}
	UPROPERTY(EditAnywhere)
	FText Name;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AItemBase> Class;
	UPROPERTY(EditAnywhere)
	EItemType Type;
	UPROPERTY(EditAnywhere)
	UTexture2D* Image;
	UPROPERTY(EditAnywhere)
	FIntPoint Size;
	UPROPERTY(EditAnywhere)
	uint32 MaxStack;
};

USTRUCT(BlueprintType)
struct FItemInstance : public FTableRowBase
{
	GENERATED_BODY()
public:
	FItemInstance() : Guid(FGuid::NewGuid()), ItemRow(FName()), bIsInStorage(false), bIsRotated(false), CurrentStack(1), bIsFromRaid(false)
	{}

	UPROPERTY(EditAnywhere)
	FGuid Guid;
	UPROPERTY(EditAnywhere)
	FName ItemRow;
	UPROPERTY(EditAnywhere)
	TArray<FGuid> ChildArray;
	UPROPERTY(EditAnywhere)
	bool bIsInStorage;
	UPROPERTY(EditAnywhere)
	bool bIsRotated;
	UPROPERTY(EditAnywhere)
	FIntPoint StoragePosition;
	UPROPERTY(EditAnywhere)
	int CurrentStack;
	UPROPERTY(EditAnywhere)
	bool bIsFromRaid;
};

class AMyCharacter;
UCLASS()
class NAKWON_API AItemBase : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// Inherited via IInteractInterface
	virtual void Interact(AMyCharacter* InteractCharacter, FText InteractionName) override;
	virtual void ShowInteractMenu(AMyCharacter* InteractCharacter) override;

	// DataBase
	virtual void LoadData(FItemInstance* NewItemInstance);
	virtual void CreateInstance(bool bFromStore);

	// Item
	void Rotate();

public:
	// Getter / Setter
	FName GetItemRow() const;
	const FItemInstance& GetItemInstance() const;
	const FItemInfo& GetItemInfo() const;
	FText GetItemName() const;
	FIntPoint GetSize() const;
protected:
	// Interact Action
	virtual void UseItem();

	virtual void TakeItem(AMyCharacter* InteractCharacter);

	virtual void ExamineItem();
protected:
	// Item Info
	UPROPERTY(EditAnywhere)
	FItemInfo ItemInfo;

	UPROPERTY(EditAnywhere)
	TArray<FText> MenuTextArray;

	// Item Instance
	UPROPERTY(EditAnywhere)
	FItemInstance ItemInstance;

	// Inherited via IInteractInterface
	virtual FText GetActorName() override;
};