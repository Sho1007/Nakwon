// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Nakwon.h"
#include "GameFramework/Actor.h"

#include "../Interface/InteractInterface.h"
#include "Engine/DataTable.h"

#include "ItemBase.generated.h"

UENUM(BlueprintType)
enum class EItemAct : uint8
{
	NONE,
	Equip,
	USE,
	TAKE,
	EXAMINE,
	SIZE,
};

class UTexture2D;
UENUM(BlueprintType)
enum class EItemType : uint8
{
	NONE,
	EQUIPMENT,
	CONSUMABLE,
	INGREDIENT,
	QUEST,
	SIZE,
};

USTRUCT(BlueprintType)
struct FItemInfo : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	FName ItemName;
	UPROPERTY(EditDefaultsOnly)
	EItemType ItemType;
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* ItemImage;
};

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
	virtual void Interact(AActor* InteractActor) override;

private:
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = true))
	FName ItemRow;
};