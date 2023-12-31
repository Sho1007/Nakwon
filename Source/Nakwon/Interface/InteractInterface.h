// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Nakwon.h"
#include "UObject/Interface.h"
#include "InteractInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AMyCharacter;
class NAKWON_API IInteractInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Interact(AMyCharacter* InteractCharacter, FText InteractionName) = 0;
	virtual void ShowInteractMenu(AMyCharacter* InteractCharacter) = 0;
	virtual FText GetActorName() = 0;
};