// Fill out your copyright notice in the Description page of Project Settings.


#include "../Weapon/WeaponBase.h"

#include <Kismet/KismetRenderingLibrary.h>
#include <Kismet/KismetMaterialLibrary.h>

#include "../../IconMaker.h"
#include "../../WeaponParts/WeaponPartsBase.h"
#include "../../WeaponParts/TestWeaponParts.h"
#include "../../WeaponParts/TEST_SMC.h"
#include "../../../Widget/Escape/EscapeWidget.h"



void AWeaponBase::SetRenderTarget()
{
	if (ParentMaterial->IsValidLowLevelFast())
	{
		WeaponImageRenderTarget = UKismetRenderingLibrary::CreateRenderTarget2D(this, ItemInfo.Width * 32, ItemInfo.Height * 32);
		WeaponImageMaterial = UKismetMaterialLibrary::CreateDynamicMaterialInstance(this, ParentMaterial);
		WeaponImageMaterial->SetTextureParameterValue(TEXT("FinalColorTexture"), WeaponImageRenderTarget);

		// Todo :
		//GetWorld()->GetFirstPlayerController()->GetHUD<AEscapeHUD>()->GetEscapeWidget()->SetRenderTarget(WeaponImageMaterial);
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