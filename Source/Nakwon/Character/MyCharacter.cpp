// Fill out your copyright notice in the Description page of Project Settings.


#include "../Character/MyCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "../HUD/BattleHUD.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	SetReplicates(true);

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultContext, 0);
		}
	}
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::Move);
		EIC->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyCharacter::Look);
	}
}

void AMyCharacter::CheckInteract()
{
	if (!IsLocallyControlled()) return;
	if (UWorld* World = GetWorld())
	{
		FVector Start = FollowCamera->GetComponentLocation() + (CameraBoom->TargetArmLength * FollowCamera->GetForwardVector());
		FVector End = Start + CheckInteractLength * FollowCamera->GetForwardVector();
		FHitResult HitResult;
		if (World->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Camera))
		{
			if (IsValid(HitResult.GetActor()))
			{
				if (IInteractInterface* Interface = Cast<IInteractInterface>(HitResult.GetActor()))
				{
					if (InteractActor != Interface)
					{
						if (InteractActor)
						{
							// Todo : Do Something before InteractActor
						}
						InteractActor = Interface;
						InteractActor->Interact(this);
					}
					return;
				}
			}
			
		}
	}
	InteractActor = nullptr;
	HideInteractMenu();
}

void AMyCharacter::ShowItemMenu(FName ItemName)
{
	if (APlayerController* PC = GetController<APlayerController>())
	{
		if (ABattleHUD* HUD = PC->GetHUD<ABattleHUD>())
		{
			HUD->ShowItemMenu(ItemName);
		}
	}
}

void AMyCharacter::HideInteractMenu()
{
	if (APlayerController* PC = GetController<APlayerController>())
	{
		if (ABattleHUD* HUD = PC->GetHUD<ABattleHUD>())
		{
			HUD->HideItemMenu();
		}
	}
}

void AMyCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (MovementVector.IsZero()) return;

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);

		CheckInteract();
	}
}

void AMyCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (LookAxisVector.IsZero()) return;

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(-LookAxisVector.Y);

		CheckInteract();
	}
}

void AMyCharacter::Interact(AActor* TargetActor)
{
}