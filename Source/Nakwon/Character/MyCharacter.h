// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Nakwon.h"
#include "GameFramework/Character.h"

#include "../Interface/InteractInterface.h"

#include "MyCharacter.generated.h"

DECLARE_DELEGATE_OneParam(FDele_Single_One_Float, float);

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
	virtual void ShowInteractMenu(AMyCharacter* InteractCharacter) override;

	bool CheckKnowItem(FName ItemName);

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
	void SetSpawnPoint(AWayout* NewSpawnPoint);

	// Interact
	void SetMenuTextArray(const TArray<FText>& NewMenuTextArray);
	const TArray<FText>& GetMenuTextArray() const;

	AActor* GetInteractActor() const;
	int GetInteractMenuIndex() const;
private:
	// Interact
	void CheckInteract();
	void DoInteract();
	UFUNCTION(Server, Reliable)
	void Req_DoInteract();
	void Req_DoInteract_Implementation();

	// Action
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void MenuSelect(const FInputActionValue& Value);
	UFUNCTION(Server, Reliable)
	void Req_MenuSelectUp();
	void Req_MenuSelectUp_Implementation();
	UFUNCTION(Server, Reliable)
	void Req_MenuSelectDown();
	void Req_MenuSelectDown_Implementation();
	void ToggleInGameMenu(const FInputActionValue& Value);
	void Aim(const FInputActionValue& Value);
	UFUNCTION(Server, Reliable)
	void Req_Aim();
	void Req_Aim_Implementation();

private:
	UFUNCTION()
	void OnRep_EscapeTime();
	UFUNCTION()
	void OnRep_InteractMenuIndex();
	UFUNCTION()
	void OnRep_MenuTextArray();
public:
	// Delegate
	FDele_Single_One_Float EscapeTimeDelegate;
private:
	// Save
	TArray<FName> KnownItemArray;
	// Inventory
	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = true))
	UInventoryComponent* InventoryComponent;

	// Interact
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = true))
	float CheckInteractLength;
	UPROPERTY(EditInstanceOnly, Replicated, Meta = (AllowPrivateAccess = true))
	AActor* CurrentInteractActor;
	UPROPERTY(EditInstanceOnly, ReplicatedUsing = OnRep_MenuTextArray, Meta = (AllowPrivateAccess = true))
	TArray<FText> MenuTextArray;
	UPROPERTY(EditInstanceOnly, ReplicatedUsing = OnRep_InteractMenuIndex, Meta = (AllowPrivateAccess = true))
	int InteractMenuIndex;

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

	UPROPERTY(EditInstanceOnly, ReplicatedUsing = OnRep_EscapeTime, Meta = (AllowPrivateAccess))
	float EscapeTime;

	// Camera Component
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = true))
	USpringArmComponent* CameraBoom;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Meta = (AllowPrivateAccess = true))
	UCameraComponent* FollowCamera;

	// Action State 
	UPROPERTY(Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	bool bIsAimed;
	UPROPERTY(Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	bool bIsStopBreath;
};