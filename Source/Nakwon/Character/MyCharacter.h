// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Nakwon.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;

struct FInputActionValue;
UCLASS()
class NAKWON_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
private:
	// Input
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = true))
	UInputMappingContext* DefaultContext;
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = true))
	UInputAction* MoveAction;
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = true))
	UInputAction* LookAction;

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