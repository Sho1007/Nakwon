// Fill out your copyright notice in the Description page of Project Settings.


#include "../Item/ItemBase.h"

#include "../Character/MyCharacter.h"

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

void AItemBase::Interact(AActor* InteractActor)
{
	AMyCharacter* Character = Cast<AMyCharacter>(InteractActor);
	if (Character)
	{
		Character->ShowItemMenu(FName(TEXT("Item")));
	}
}