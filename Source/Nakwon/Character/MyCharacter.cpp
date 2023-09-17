// Fill out your copyright notice in the Description page of Project Settings.


#include "../Character/MyCharacter.h"

#include "Net/UnrealNetwork.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

// Ability
#include "Abilities/CharacterAbilitySystemComponent.h"
#include "Abilities/CharacterGameplayAbility.h"
#include "Abilities/AttributeSets/CharacterAttributeSetBase.h"

#include "../HUD/BattleHUD.h"
#include "../Component/InventoryComponent.h"

// Zone
#include "../Actor/Wayout.h"

// Sets default values
AMyCharacter::AMyCharacter(const FObjectInitializer& ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetMesh(), TEXT("head"));

	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	//CameraBoom->AttachToComponent();

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(FName(TEXT("InventoryComponent")));
}

void AMyCharacter::Interact(AMyCharacter* InteractCharacter, FText InteractionName)
{
}

void AMyCharacter::ShowInteractMenu()
{
	// Todo : Check Health StateComponent if dead show Interact Menu
	//if ()
	return;
	if (APlayerController* PC = GetController<APlayerController>())
	{
		if (ABattleHUD* HUD = PC->GetHUD<ABattleHUD>())
		{
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

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true);
		InventoryComponent->SetIsReplicated(true);
	}

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultContext, 0);
		}

		//DisableInput(GetController<APlayerController>());
	}
}

void AMyCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyCharacter, CurrentInteractActor);
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckInteract();

	// Escape
	if (bCanEscape)
	{
		CurrentEscapeTime += DeltaTime;
		if (CurrentEscapeTime > MaxEscapeTime)
		{
			bCanEscape = false;
			// Todo : Escape
			UE_LOG(LogTemp, Warning, TEXT("AMyCharacter::Tick : %s Escaped"), *GetName());
			this->GetController<APlayerController>()->ClientTravel(FString::Printf(TEXT("/Game/Levels/L_MainMenu")), TRAVEL_Relative, true);
		}
	}
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::Move);
		EIC->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyCharacter::Look);
		EIC->BindAction(MenuSelectAction, ETriggerEvent::Started, this, &AMyCharacter::MenuSelect);
		EIC->BindAction(InteractAction, ETriggerEvent::Started, this, &AMyCharacter::DoInteract);
		EIC->BindAction(InGameMenuAction, ETriggerEvent::Started, this, &AMyCharacter::ToggleInGameMenu);
		EIC->BindAction(AimAction, ETriggerEvent::Started, this, &AMyCharacter::Aim);
	}
}

void AMyCharacter::EnterZone(FName ZoneName)
{
	ZoneList.Add(ZoneName);
}

void AMyCharacter::LeaveZone(FName ZoneName)
{
	ZoneList.Remove(ZoneName);
}

void AMyCharacter::Escape(AWayout* Wayout, float NewEscapeTime)
{
	if (SpawnPoint)
	{
		TArray<AWayout*> DestinationArray = SpawnPoint->GetDestinationArray();
		for (AWayout* Destination : DestinationArray)
		{
			if (Destination == Wayout)
			{
				UE_LOG(LogTemp, Warning, TEXT("AMyCharacter::Escape : Start To Escape"));
				EscapeWayout = Wayout;
				MaxEscapeTime = NewEscapeTime;
				CurrentEscapeTime = 0.0f;
				bCanEscape = true;
				// Todo :
				// 1. 로딩 바 띄우기
				// 2. 로딩 다 되면 탈출 시키기
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AMyCharacter::Escape : Invalid SpawnPoint"));
	}
}

void AMyCharacter::StopEscape(AWayout* Wayout)
{
	if (EscapeWayout && EscapeWayout == Wayout)
	{
		EscapeWayout = nullptr;
		bCanEscape = false;
		// Todo :
		// 1. 로딩 바 지우기
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
					if (CurrentInteractActor != HitResult.GetActor())
					{
						if (CurrentInteractActor)
						{
							// Todo : Do Something before InteractActor
							HideInteractMenu();
						}
						CurrentInteractActor = HitResult.GetActor();
						Interface->ShowInteractMenu();
					}
					return;
				}
			}

		}
	}
	CurrentInteractActor = nullptr;
	HideInteractMenu();
}

void AMyCharacter::DoInteract()
{
	if (CurrentInteractActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("AMyCharacter::DoInteract : %s"), *CurrentInteractActor->GetName());
		if (APlayerController* PlayerControlelr = GetController<APlayerController>())
		{
			if (ABattleHUD* HUD = PlayerControlelr->GetHUD<ABattleHUD>())
			{
				Cast<IInteractInterface>(CurrentInteractActor)->Interact(this, HUD->GetSelectInteractText());
			}
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
	}
}

void AMyCharacter::MenuSelect(const FInputActionValue& Value)
{
	float WheelValue = Value.Get<float>();
	if (CurrentInteractActor)
	{
		if (APlayerController* PC = GetController<APlayerController>())
		{
			if (ABattleHUD* HUD = PC->GetHUD<ABattleHUD>())
			{
				HUD->SelectMenu(WheelValue);
			}
		}
	}
}

void AMyCharacter::ToggleInGameMenu(const FInputActionValue& Value)
{
	if (APlayerController* PC = GetController<APlayerController>())
	{
		if (ABattleHUD* HUD = PC->GetHUD<ABattleHUD>())
		{
			HUD->ToggleInGameMenu();
		}
	}
}

void AMyCharacter::Aim(const FInputActionValue& Value)
{
	if (bIsAimed) bIsAimed = false;
	else bIsAimed = true;
}