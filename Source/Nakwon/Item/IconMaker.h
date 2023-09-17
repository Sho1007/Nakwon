// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IconMaker.generated.h"


class USceneCaptureComponent2D;
class UPointLightComponent;
UCLASS()
class NAKWON_API AIconMaker : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIconMaker();
public:
	void Capture(AActor* TargetActor, FVector CaptureLocation, FRotator CaptureRotation);

private:
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = true))
	USceneCaptureComponent2D* SceneCaptureComponent;
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = true))
	UPointLightComponent* PointLightComponent;
};
