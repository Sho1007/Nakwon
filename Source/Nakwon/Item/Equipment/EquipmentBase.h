// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ItemBase.h"
#include "EquipmentBase.generated.h"

DECLARE_DELEGATE_OneParam(FDele_Single_Int, int)

/**
 * 
 */

USTRUCT(BlueprintType)
struct FEquipmentInfo : public FTableRowBase
{
	GENERATED_BODY()
public:
	FEquipmentInfo() : EquipmentType(EEquipmentType::NONE), MaxDurability(1)
	{

	}
	UPROPERTY(EditDefaultsOnly)
	EEquipmentType EquipmentType;
	UPROPERTY(EditDefaultsOnly)
	uint32 MaxDurability;
};

USTRUCT(BlueprintType)
struct FEquipmentInstance : public FTableRowBase
{
	GENERATED_BODY()
public:
	FEquipmentInstance() : CurrentDurability(1)
	{
	}

	UPROPERTY(EditAnywhere)
	uint32 CurrentDurability;
};

UCLASS()
class NAKWON_API AEquipmentBase : public AItemBase
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
public:
	void Init();

	// DataBase
	virtual void LoadData(FItemInstance* NewItemInstance) override;
	virtual void CreateInstance(bool bFromStore) override;

	virtual void Interact(AMyCharacter* InteractCharacter, FText InteractionName) override;

	UFUNCTION(NetMulticast, Reliable)
	virtual void SetEquipped(AMyCharacter* InteractCharacter, EEquipmentSlotType SlotType);
	virtual void SetEquipped_Implementation(AMyCharacter* InteractCharacter, EEquipmentSlotType SlotType);

public:
	// Getter / Setter
	const FEquipmentInfo& GetEquipmentInfo() const;
	const FEquipmentInstance& GetEquipmentInstance() const;


	void SetCurrentDurability(int NewCurrentDurability);

public:
	// OnRep
	UFUNCTION()
	void OnRep_EquipmentInstance();

public:
	// Delegate
	FDele_Single_Int Delegate_CurrrentDurability;

protected:
	UPROPERTY(EditAnywhere)
	FEquipmentInfo EquipmentInfo;
	UPROPERTY(ReplicatedUsing = OnRep_EquipmentInstance, EditAnywhere)
	FEquipmentInstance EquipmentInstance;
};