// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../Nakwon.h"
#include "AbilitySystemComponent.h"
#include "CharacterAbilitySystemComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FDele_ReceivedDamage, UCharacterAbilitySystemComponent*, SourceASC, float, UnmitigatedDamage, float, MitigatedDamage);

/**
 * 
 */
UCLASS(Blueprintable)
class NAKWON_API UCharacterAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	bool bCharacterAbilitiesGiven = false;
	bool bStartupEffectsApplied = false;

	FDele_ReceivedDamage ReceivedDamage;

	virtual void ReceiveDamage(UCharacterAbilitySystemComponent* SourceASC, float UnmitigatedDamage, float MitigatedDamage);
};
