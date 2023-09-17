// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Nakwon.h"
#include "GameFramework/Actor.h"

#include <Engine/DataTable.h>
#include <Misc/Guid.h>
#include "../Interface/InteractInterface.h"

#include "ItemBase.generated.h"

USTRUCT(BlueprintType)
struct FItemInfo : public FTableRowBase
{
	GENERATED_BODY()
public:
	FItemInfo()
		: Name(FText()), Class(nullptr), Type(EItemType::NONE), Image(nullptr), Width(0), Height(0)
	{
	}
	UPROPERTY(EditDefaultsOnly)
	FText Name;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AItemBase> Class;
	UPROPERTY(EditDefaultsOnly)
	EItemType Type;
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* Image;
	UPROPERTY(EditDefaultsOnly)
	uint32 Width;
	UPROPERTY(EditDefaultsOnly)
	uint32 Height;
	UPROPERTY(EditDefaultsOnly)
	uint32 MaxStack;
};
USTRUCT(BlueprintType)
struct FItemInstance : public FTableRowBase
{
	GENERATED_BODY()
public:
	FItemInstance() {}

	UPROPERTY(EditDefaultsOnly)
	FGuid Guid;
	UPROPERTY(EditDefaultsOnly)
	FName ItemRow;
	UPROPERTY(EditDefaultsOnly)
	uint32 CurrentStack;
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

	// DataBase
	virtual void LoadData(FItemInfo* ItemInfo, FItemInstance* ItemInstance);

public:
	// Getter / Setter
	FName GetItemRow() const;
	FItemInstance GetItemInstance() const;

protected:
	// Interact Action
	virtual void UseItem();

	virtual void TakeItem(AMyCharacter* InteractCharacter);
	
	virtual void ExamineItem();
protected:
	FGuid Guid;

	// Item Info
	UPROPERTY(EditDefaultsOnly)
	FText Name;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AItemBase> Class;
	UPROPERTY(EditDefaultsOnly)
	EItemType Type;
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* Image;
	UPROPERTY(EditDefaultsOnly)
	uint32 Width;
	UPROPERTY(EditDefaultsOnly)
	uint32 Height;
	UPROPERTY(EditDefaultsOnly)
	uint32 MaxStack;

	// Instance Info
	UPROPERTY(EditDefaultsOnly)
	uint32 CurrentStack;
};