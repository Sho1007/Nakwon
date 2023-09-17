// Fill out your copyright notice in the Description page of Project Settings.


#include "../Actor/Zone.h"

#include <Components/BoxComponent.h>

#include "../Character/MyCharacter.h"

// Sets default values
AZone::AZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	SetRootComponent(BoxComponent);
	BoxComponent->SetCollisionProfileName(TEXT("Zone"));
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AZone::OnBeginOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AZone::OnEndOverlap);
}

// Called when the game starts or when spawned
void AZone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AZone::EnterPlayer(AMyCharacter* EnteredPlayer)
{
	EnteredPlayer->EnterZone(ZoneName);
}

void AZone::LeavePlayer(AMyCharacter* EnteredPlayer)
{
	EnteredPlayer->LeaveZone(ZoneName);
}

void AZone::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AMyCharacter* Character = Cast<AMyCharacter>(OtherActor))
	{
		EnterPlayer(Character);
	}
}

void AZone::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		if (AMyCharacter* Character = Cast<AMyCharacter>(OtherActor))
		{
			LeavePlayer(Character);
		}
	}
}