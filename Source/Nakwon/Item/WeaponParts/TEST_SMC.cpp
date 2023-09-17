// Fill out your copyright notice in the Description page of Project Settings.


#include "../WeaponParts/TEST_SMC.h"


void UTEST_SMC::BeginPlay()
{
	Super::BeginPlay();

	UStaticMeshComponent* SMC = NewObject<UStaticMeshComponent>(this);
	SMC->RegisterComponent();
	SMC->AttachToComponent(this, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true));
	if (ChildStaticMesh)
		SMC->SetStaticMesh(ChildStaticMesh);
}