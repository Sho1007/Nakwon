// Fill out your copyright notice in the Description page of Project Settings.


#include "../Actor/Wayout.h"

#include "../Character/MyCharacter.h"

const TArray<AWayout*>& AWayout::GetDestinationArray() const
{
	return DestinationArray;
}

int AWayout::GetPlayerCount() const
{
	return PlayerCount;
}

bool AWayout::IsSpawnable() const
{
	return SpawnPointArray.Num() > PlayerCount;
}

void AWayout::SetSpawnPoint(AMyCharacter* Character)
{
	Character->SetSpawnPoint(this);
	FHitResult HitResult;
	FVector SpawnLocation = this->GetActorLocation();
	SpawnLocation.X += SpawnPointArray[PlayerCount].GetLocation().X * GetActorScale3D().X;
	SpawnLocation.Y += SpawnPointArray[PlayerCount].GetLocation().Y * GetActorScale3D().Y;
	Character->SetActorLocationAndRotation(SpawnLocation, SpawnPointArray[PlayerCount].GetRotation().Rotator() + this->GetActorRotation(), false, &HitResult, ETeleportType::ResetPhysics);
	PlayerCount++;
}

void AWayout::EnterPlayer(AMyCharacter* EnteredPlayer)
{
	Super::EnterPlayer(EnteredPlayer);
	EnteredPlayer->Escape(this, 5.0f);
}

void AWayout::LeavePlayer(AMyCharacter* LeavedPlayer)
{
	Super::LeavePlayer(LeavedPlayer);
	LeavedPlayer->StopEscape(this);
}