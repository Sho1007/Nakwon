// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "../Interface/InteractInterface.h"

#include "ItemBase.generated.h"

USTRUCT(BlueprintType)
struct FItemInfo
{
	GENERATED_BODY()
public:

};

UCLASS()
class NAKWON_API AItemBase : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// Inherited via IInteractInterface
	virtual void Interact(AActor* InteractActor) override;

private:
	FItemInfo ItemInfo;
};
