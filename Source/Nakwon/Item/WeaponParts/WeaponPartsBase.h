// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ItemBase.h"
#include "WeaponPartsBase.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EWeaponPartsType : uint8
{
	NONE,
	GRIP,
	FOREGRIP,
	IRONSIGHTPOST,
	IRONSIGHTREAR,
	IRONSIGHTFRONT,
	SCOPE,
	MUZZLE,
	STOCK,
	RAIL,
	SIZE,
};

USTRUCT(BlueprintType)
struct FWeaponPartsSlot
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	FText SlotName;
	UPROPERTY(EditDefaultsOnly)
	TArray<EWeaponPartsType> WeaponPartsTypeArray;
	UPROPERTY(VisibleAnywhere)
	AWeaponPartsBase* WeaponParts;
};

UCLASS()
class NAKWON_API AWeaponPartsBase : public AItemBase
{
	GENERATED_BODY()
	
public:
	EWeaponPartsType GetWeaponPartsType() const;
	
	const TMap<FName, float>& GetWeaponPartsStatus() const;
protected:
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = true))
	TMap<FName, float> Status;
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = true))
	EWeaponPartsType WeaponPartsType;
};