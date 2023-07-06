// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Nakwon.h"
#include "GameFramework/Character.h"

#include "AbilitySystemInterface.h"
#include "GamePlayTagContainer.h"
#include "../Interface/InteractInterface.h"

#include "MyCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDele_CharacterDied, AMyCharacter*, DiedCharacter);

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UInventoryComponent;

class UCharacterAbilitySystemComponent;
class UCharacterAttributeSetBase;
class UGameplayEffect;
class UCharacterGameplayAbility;

struct FInputActionValue;
struct FItemInfo;
UCLASS()
class NAKWON_API AMyCharacter : public ACharacter, public IInteractInterface, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintAssignable, Category = "Character|State")
	FDele_CharacterDied OnCharacterDied;

public:
	// Interact
	// Inherited via IInteractInterface
	virtual void Interact(AMyCharacter* InteractCharacter, FText InteractionName) override;
	virtual void ShowInteractMenu() override;
	void HideInteractMenu();

	// Ability
	// Inherited via IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable, Category = "Character|Attributes")
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Character|Attributes")
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Character|Attributes")
	float GetMana() const;

	UFUNCTION(BlueprintCallable, Category = "Character|Attributes")
	float GetMaxMana() const;

	UFUNCTION(BlueprintCallable, Category = "Character|State")
	virtual bool IsAlive() const;

	UFUNCTION(BlueprintCallable, Category = "Character|Ability")
	virtual int32 GetAbilityLevel(AbilityID ID) const;

	virtual void RemoveCharacterAbilities();

	virtual void Die();

	UFUNCTION(BlueprintCallable, Category = "Character|State")
	virtual void FinishDying();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	// Interact
	void CheckInteract();
	void DoInteract();

	// Action
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void MenuSelect(const FInputActionValue& Value);

	// Ability
	virtual void AddCharacterAbilities();

	virtual void InitializeAttributes();

	virtual void AddStartupEffects();

	virtual void SetHealth(float Health);
	virtual void SetMana(float Mana);

private:
	// Ability
	TWeakObjectPtr<UCharacterAbilitySystemComponent> AbilitySystemComponent;

	TWeakObjectPtr<UCharacterAttributeSetBase> AttributeSetBase;

	FGameplayTag DeadTag;
	FGameplayTag EffectRemoveOnDeathTag;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character", Meta = (AllowPrivateAccess = true))
	FText CharacterName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Animation", Meta = (AllowPrivateAccess = true))
	UAnimMontage* DeathMontage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Abilities", Meta = (AllowPrivateAccess = true))
	TArray<TSubclassOf<UCharacterGameplayAbility>> CharacterAbilities;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Abilities", Meta = (AllowPrivateAccess = true))
	TSubclassOf<UGameplayEffect> DefaultAttributes;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Abilities", Meta = (AllowPrivateAccess = true))
	TArray<TSubclassOf<UGameplayEffect>> StartupAttributes;

	// Inventory
	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = true))
	UInventoryComponent* InventoryComponent;

	// Interact
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = true))
	float CheckInteractLength;

	UPROPERTY(Replicated, Meta = (AllowPrivateAccess = true))
	AActor* CurrentInteractActor;

	// Input
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = true))
	UInputMappingContext* DefaultContext;
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = true))
	UInputAction* MoveAction;
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = true))
	UInputAction* LookAction;
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = true))
	UInputAction* MenuSelectAction;
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = true))
	UInputAction* InteractAction;

	// Camera Component
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = true))
	USpringArmComponent* CameraBoom;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Meta = (AllowPrivateAccess = true))
	UCameraComponent* FollowCamera;

	// Action State 
	UPROPERTY(BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	bool bIsAimed;
	UPROPERTY(BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	bool bIsStopBreath;
};