// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../EquipmentBase.h"
#include "WeaponBase.generated.h"

/**
 * 
 */
class UTextureRenderTarget2D;
class UMaterialInstanceDynamic;
class UMaterialInterface;
class AWeaponPartsBase;
class UStaticMeshComponent;
class UTEST_SMC;
UCLASS()
class NAKWON_API AWeaponBase : public AEquipmentBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(CallInEditor)
	void SetRenderTarget();

	UFUNCTION(CallInEditor)
	void Capture();

	UFUNCTION(CallInEditor)
	void AddWeaponParts();

	const TArray<AWeaponPartsBase*>& GetWeaponPartsArray() const;
	
	UTextureRenderTarget2D* GetRenderTarget() const;
private:
	// Test : Modify Weapon
	UPROPERTY(EditInstanceOnly, Meta = (AllowPrivateAccess))
	UStaticMesh* TestStaticMesh;
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess))
	TSubclassOf<UTEST_SMC> SMCClass;
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess))
	TArray<AWeaponPartsBase*> WeaponPartsArray;
	UPROPERTY(EditInstanceOnly, Meta = (AllowPrivateAccess))
	TSubclassOf<AWeaponPartsBase> WeaponPartsClass;


	// Test : Dynamic Weapon Image (When Add / Remove WeaponParts)
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess))
	FRotator CaptureRotation;
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess))
	FVector CaptureLocation;

	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess))
	UMaterialInterface* ParentMaterial;
	UPROPERTY(EditInstanceOnly, Meta = (AllowPrivateAccess))
	UTextureRenderTarget2D* WeaponImageRenderTarget;
	UPROPERTY(EditInstanceOnly, Meta = (AllowPrivateAccess))
	UMaterialInstanceDynamic* WeaponImageMaterial;
};