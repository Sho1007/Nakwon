// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Nakwon.h"
#include "GameFramework/Actor.h"

#include "../Interface/InteractInterface.h"
#include "Engine/DataTable.h"

#include "ItemBase.generated.h"

USTRUCT(BlueprintType)
struct FItemInfo : public FTableRowBase
{
	GENERATED_BODY()
public:
	FItemInfo()
		: ItemName(FText()), ItemType(EItemType::NONE), ItemImage(nullptr), MaxStack(0)
	{
	}
	UPROPERTY(EditDefaultsOnly)
	FText ItemName;
	UPROPERTY(EditDefaultsOnly)
	EItemType ItemType;
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* ItemImage;
	UPROPERTY(EditDefaultsOnly)
	int32 MaxStack;
};

USTRUCT(BlueprintType)
struct FItemInstance
{
	GENERATED_BODY()
public:
	FItemInstance()
		: ItemRow(FName()), CurrentStack(0)
	{
	}
	FItemInstance(FName NewItemRow, int32 NewCurrentStack = 0)
		: ItemRow(NewItemRow), CurrentStack(NewCurrentStack)
	{
	}
	UPROPERTY(EditAnywhere)
	FName ItemRow;
	UPROPERTY(EditAnywhere)
	int32 CurrentStack;
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
	virtual void ShowInteractMenu() override;

public:
	// Getter / Setter
	FName GetItemRow() const;

private:
	// Interact Action
	virtual void UseItem();

	virtual void TakeItem(AMyCharacter* InteractCharacter);
	
	virtual void ExamineItem();
protected:
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = true))
	FName ItemRow;
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = true))
	FItemInfo ItemInfo;
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = true))
	TArray<FText> ItemMenuArray;
};