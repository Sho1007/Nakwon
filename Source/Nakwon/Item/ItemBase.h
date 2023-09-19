// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Nakwon.h"
#include "GameFramework/Actor.h"

#include <Engine/DataTable.h>
#include <Misc/Guid.h>
#include "../Interface/InteractInterface.h"

#include "ItemBase.generated.h"

// Inventory에 존재하면, 표현하기 위한 구조체
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
	TMap<FName, int32> IntMap;
	UPROPERTY(EditDefaultsOnly)
	TMap<FName, float> FloatMap;
	UPROPERTY(EditDefaultsOnly)
	TArray<FGuid> ChildArray;
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
	virtual void LoadData(FItemInstance* ItemInstance);
	virtual void CreateInstance();

public:
	// Getter / Setter
	FName GetItemRow() const;
	FItemInstance GetItemInstance() const;
	FText GetItemName() const;

protected:
	// Interact Action
	UFUNCTION(Server, Reliable)
	virtual void UseItem();
	virtual void UseItem_Implementation();

	UFUNCTION(Server, Reliable)
	virtual void TakeItem(AMyCharacter* InteractCharacter);
	virtual void TakeItem_Implementation(AMyCharacter* InteractCharacter);

	UFUNCTION(Server, Reliable)
	virtual void ExamineItem();
	virtual void ExamineItem_Implementation();
protected:
	// Item Info
	UPROPERTY(EditDefaultsOnly)
	FItemInfo ItemInfo;

	UPROPERTY(EditDefaultsOnly)
	TArray<FText> MenuTextArray;

	// Item Instance
	UPROPERTY(EditDefaultsOnly)
	FItemInstance ItemInstance;
};