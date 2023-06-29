// Fill out your copyright notice in the Description page of Project Settings.


#include "../Item/ItemBase.h"

#include "../HUD/BattleHUD.h"

// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemBase::Interact(FName InteractionName)
{
}

void AItemBase::ShowInteractMenu()
{
	if (ABattleHUD* HUD = GetWorld()->GetFirstPlayerController()->GetHUD<ABattleHUD>())
	{
		HUD->ShowInteractMenu(ItemRow);
	}
}