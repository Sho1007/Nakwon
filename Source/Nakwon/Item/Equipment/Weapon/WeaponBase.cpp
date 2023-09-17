// Fill out your copyright notice in the Description page of Project Settings.


#include "../Weapon/WeaponBase.h"

#include <Kismet/KismetRenderingLibrary.h>
#include <Kismet/KismetMaterialLibrary.h>

#include "../../../HUD/BattleHUD.h"
#include "../../IconMaker.h"
#include "../../WeaponParts/WeaponPartsBase.h"
#include "../../WeaponParts/TestWeaponParts.h"
#include "../../WeaponParts/TEST_SMC.h"

void AWeaponBase::SetRenderTarget()
{
	if (ParentMaterial->IsValidLowLevelFast())
	{
		WeaponImageRenderTarget = UKismetRenderingLibrary::CreateRenderTarget2D(this, Width * 32, Height * 32);
		WeaponImageMaterial = UKismetMaterialLibrary::CreateDynamicMaterialInstance(this, ParentMaterial);
		WeaponImageMaterial->SetTextureParameterValue(TEXT("FinalColorTexture"), WeaponImageRenderTarget);
		GetWorld()->GetFirstPlayerController()->GetHUD<ABattleHUD>()->SetRenderTarget(WeaponImageMaterial);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AWeaponBase::SetRenderTarget : ParentMaterial is Invalid"));
	}
}

void AWeaponBase::Capture()
{
	AIconMaker* IconMaker = GetWorld()->SpawnActor<AIconMaker>();
	IconMaker->Capture(this, CaptureLocation, CaptureRotation);
}

void AWeaponBase::AddWeaponParts()
{
	if (WeaponPartsClass)
	{
		
		/*if (AWeaponPartsBase* NewWeaponParts = GetWorld()->SpawnActor<AWeaponPartsBase>(WeaponPartsClass))
		{
			NewWeaponParts->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true), TEXT("Handguard"));
			WeaponPartsArray.Add(NewWeaponParts);
		}*/
		/*if (UTestWeaponParts* WeaponParts = NewObject<UTestWeaponParts>(this, UTestWeaponParts::StaticClass(), TEXT("TestChildActorComponent")))
		{
			WeaponParts->SetChildActorClass(WeaponPartsClass);
			WeaponParts->RegisterComponent();
			WeaponParts->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true), TEXT("Handguard"));
			WeaponParts->ResetRelativeTransform();
		}*/
		//this->GetComponentsByClass(;
		// Test Create UStaticMeshComponent At Runtime

		UStaticMeshComponent* SMC = NewObject<UTEST_SMC>(this, SMCClass, TEXT("StaticMeshComponent"));
		SMC->RegisterComponent();
		SMC->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true), TEXT("Handguard"));
		SMC->ResetRelativeTransform();
		//SMC->SetStaticMesh(TestStaticMesh);
	}
}

const TArray<AWeaponPartsBase*>& AWeaponBase::GetWeaponPartsArray() const
{
	return WeaponPartsArray;
}

UTextureRenderTarget2D* AWeaponBase::GetRenderTarget() const
{
	return WeaponImageRenderTarget;
}