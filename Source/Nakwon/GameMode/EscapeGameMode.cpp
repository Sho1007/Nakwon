// Fill out your copyright notice in the Description page of Project Settings.


#include "../GameMode/EscapeGameMode.h"

#include <EngineUtils.h>

#include "../Actor/Wayout.h"

void AEscapeGameMode::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("AEscapeGameMode::BeginPlay"));

	for (TActorIterator<AWayout> It(GetWorld()); It; ++It)
	{
		WayoutArray.Add(*It);
	}

	UE_LOG(LogTemp, Warning, TEXT("AEscapeGameMode::BeginPlay : Wayout Count : %d"), WayoutArray.Num());
}

void AEscapeGameMode::SetSpawnPoint(AMyCharacter* Character)
{
	bool bIsSetted = false;
	for (int i = 0; i < WayoutArray.Num(); ++i)
	{
		if (i < WayoutArray.Num() - 1)
		{
			// ������ ���Ұ� �ƴ� ��
			if (WayoutArray[i]->GetPlayerCount() == WayoutArray[i + 1]->GetPlayerCount())
			{
				// ���Ⱑ �߰� ������ ����
				if (WayoutArray[i]->IsSpawnable())
				{
					WayoutArray[i]->SetSpawnPoint(Character);
					bIsSetted = true;
					break;
				}
			}
		}
		else
		{
			// ������ ������ ��
			if (WayoutArray[i]->IsSpawnable())
			{
				WayoutArray[i]->SetSpawnPoint(Character);
				bIsSetted = true;
				break;
			}
		}
	}

	if (bIsSetted == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AEscapeGameMode::SetSpawnPoint : Player Character Count is more than SpawnPoint Count"));
	}
}