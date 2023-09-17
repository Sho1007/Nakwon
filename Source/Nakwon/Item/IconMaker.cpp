// Fill out your copyright notice in the Description page of Project Settings.


#include "../Item/IconMaker.h"

#include <Components/SceneCaptureComponent2D.h>
#include <Components/PointLightComponent.h>
#include <Engine/TextureRenderTarget2D.h>
#include <Kismet/KismetRenderingLibrary.h>

#include "Equipment/Weapon/WeaponBase.h"
#include "WeaponParts/WeaponPartsBase.h"

// Sets default values
AIconMaker::AIconMaker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent")));

	SceneCaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCaptureComponent"));
	SceneCaptureComponent->SetupAttachment(RootComponent);
	SceneCaptureComponent->bCaptureEveryFrame = false;
	SceneCaptureComponent->bCaptureOnMovement = false;
	SceneCaptureComponent->ShowFlags.Atmosphere = false;
	SceneCaptureComponent->ShowFlags.Cloud = false;
	SceneCaptureComponent->ShowFlags.Fog = false;
	SceneCaptureComponent->ShowFlags.DirectionalLights = false;
	SceneCaptureComponent->FOVAngle = 6.0f;

	PointLightComponent = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLightComponent"));
	PointLightComponent->SetupAttachment(RootComponent);
	PointLightComponent->SetRelativeLocation(FVector(-30, 10, 10));
	PointLightComponent->Intensity = 1000.0f;
	//PointLightComponent->SetLightBrightness();
}

void AIconMaker::Capture(AActor* TargetActor, FVector CaptureLocation, FRotator CaptureRotation)
{
	if (AWeaponBase* Weapon = Cast<AWeaponBase>(TargetActor))
	{
		if (UTextureRenderTarget2D* RenderTarget = Weapon->GetRenderTarget())
		{
			SceneCaptureComponent->TextureTarget = RenderTarget;
			SceneCaptureComponent->ShowOnlyActorComponents(Weapon, true);
			SceneCaptureComponent->ShowOnlyActorComponents(this);
			const TArray<AWeaponPartsBase*>& WeaponPartsArray = Weapon->GetWeaponPartsArray();
			for (auto WeaponParts : WeaponPartsArray)
			{
				SceneCaptureComponent->ShowOnlyActors.Add(WeaponParts);
			}
			// Todo : SetIconMaker Location to (Weapon Location + Offset);
			this->AttachToActor(Weapon, FAttachmentTransformRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepWorld, false));
			this->SetActorRelativeTransform(FTransform());
			SceneCaptureComponent->SetRelativeLocation(CaptureLocation);
			this->SetActorRelativeRotation(CaptureRotation);
			SceneCaptureComponent->CaptureScene();
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("AIconMaker::Capture : RenderTarget is NULL"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AIconMaker::Capture : Invalid TargetActor"));
	}
	//Destroy();
}