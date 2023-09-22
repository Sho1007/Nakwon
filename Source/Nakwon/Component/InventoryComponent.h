// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Nakwon.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


class AItemBase;
class AEquipmentBase;
class AStorageEquipmentBase;
UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NAKWON_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	UFUNCTION(Server, Reliable)
	void TakeItem(AItemBase* TargetItem);
	void TakeItem_Implementation(AItemBase* TargetItem);
	
	UFUNCTION(Server, Reliable)
	void EquipItem(EEquipmentSlotType SlotType, AEquipmentBase* TargetEquipment);
	void EquipItem_Implementation(EEquipmentSlotType SlotType, AEquipmentBase* TargetEquipment);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	AItemBase* OnSlingWeaponSlot = nullptr;

	TArray<AEquipmentBase*> EquipmentArray;

	AStorageEquipmentBase* RigSlot;
	AStorageEquipmentBase* PocketSlot;
	AStorageEquipmentBase* BackpackSlot;
	AStorageEquipmentBase* PouchSlot;
};