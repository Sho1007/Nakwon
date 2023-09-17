// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Nakwon.h"
#include "GameFramework/Character.h"

#include "../Interface/InteractInterface.h"

#include "MyCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UInventoryComponent;

class UCharacterAbilitySystemComponent;
class UCharacterAttributeSetBase;
class UGameplayEffect;
class UCharacterGameplayAbility;

// Zone / Escape
class AWayout;

struct FInputActionValue;
struct FItemInfo;
UCLASS()
class NAKWON_API AMyCharacter : public ACharacter, public IInteractInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter(const FObjectInitializer& ObjectInitializer);

public:
	// Interact
	// Inherited via IInteractInterface
	virtual void Interact(AMyCharacter* InteractCharacter, FText InteractionName) override;
	virtual void ShowInteractMenu() override;
	void HideInteractMenu();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Zone
	void EnterZone(FName ZoneName);
	void LeaveZone(FName ZoneName);

	void Escape(AWayout* Wayout, float NewEscapeTime);
	void StopEscape(AWayout* Wayout);

private:
	// Interact
	void CheckInteract();
	void DoInteract();

	// Action
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void MenuSelect(const FInputActionValue& Value);
	void ToggleInGameMenu(const FInputActionValue& Value);
	void Aim(const FInputActionValue& Value);

private:
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
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = true))
	UInputAction* InGameMenuAction;
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = true))
	UInputAction* AimAction;

	// Zone
	UPROPERTY(EditInstanceOnly, Meta = (AllowPrivateAccess = true))
	TSet<FName> ZoneList;
	UPROPERTY(EditInstanceOnly, Meta = (AllowPrivateAccess = true))
	AWayout* SpawnPoint;
	AWayout* EscapeWayout;
	// Escape
	bool bCanEscape = false;
	float MaxEscapeTime;
	float CurrentEscapeTime;

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