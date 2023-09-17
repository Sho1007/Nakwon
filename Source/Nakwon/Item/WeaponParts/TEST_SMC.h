// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TEST_SMC.generated.h"

/**
 * 
 */
UCLASS()
class NAKWON_API UTEST_SMC : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess))
	UStaticMesh* ChildStaticMesh;
};
