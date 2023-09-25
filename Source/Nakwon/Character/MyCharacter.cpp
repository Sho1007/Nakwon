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

#include "../Component/InventoryComponent.h"
#include "../Widget/Escape/EscapeWidget.h"

// Zone
#include "../Actor/Wayout.h"

// PlayerController
#include "../PlayerController/EscapePlayerController.h"

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

void AMyCharacter::ShowInteractMenu(AMyCharacter* InteractCharacter)
{
	// Todo : Check Health StateComponent if dead show Interact Menu
	//if ()
	return;
}

bool AMyCharacter::CheckKnowItem(FName ItemName)
{
	return KnownItemArray.Find(ItemName) != NULL;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("AMyCharacter::BeginPlay : %s"), *GetName());

	if (HasAuthority())
	{
		SetReplicates(true);
		InventoryComponent->SetIsReplicated(true);
		
	}

	if (IsLocallyControlled())
	{
		if (AEscapePlayerController* EscapePC = GetController<AEscapePlayerController>())
		{
			EscapePC->SetSpawnPoint();
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(EscapePC->GetLocalPlayer()))
			{
				Subsystem->AddMappingContext(DefaultContext, 0);
			}
		}
	}
}

void AMyCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyCharacter, CurrentInteractActor);
	DOREPLIFETIME(AMyCharacter, EscapeTime);
	DOREPLIFETIME(AMyCharacter, MenuTextArray);
	DOREPLIFETIME(AMyCharacter, bIsStopBreath);
	DOREPLIFETIME(AMyCharacter, bIsAimed);
	DOREPLIFETIME(AMyCharacter, InteractMenuIndex);
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority() == false) return;

	//UE_LOG(LogTemp, Warning, TEXT("AMyCharacter::Tick"));
	CheckInteract();

	// Escape
	if (bCanEscape)
	{
		EscapeTime -= DeltaTime;
		if (IsLocallyControlled()) EscapeTimeDelegate.ExecuteIfBound(EscapeTime);
		if (EscapeTime <= 0)
		{
			bCanEscape = false;
			// Todo : Escape
			UE_LOG(LogTemp, Warning, TEXT("AMyCharacter::Tick : %s Escaped"), *GetName());
			this->GetController<APlayerController>()->ClientTravel(FString::Printf(TEXT("/Game/Levels/L_MainMenu")), ETravelType::TRAVEL_Absolute);
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
				EscapeTime = NewEscapeTime;
				EscapeTimeDelegate.ExecuteIfBound(EscapeTime);
				bCanEscape = true;

				if (AEscapePlayerController* PC = GetController<AEscapePlayerController>())
				{
					PC->ShowEscapeProgress();
				}
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
		if (AEscapePlayerController* PC = GetController<AEscapePlayerController>())
		{
			PC->HideEscapeProgress();
		}
		// Todo :
		// 1. 로딩 바 지우기
	}
}

void AMyCharacter::SetSpawnPoint(AWayout* NewSpawnPoint)
{
	SpawnPoint = NewSpawnPoint;
}

void AMyCharacter::SetMenuTextArray(const TArray<FText>& NewMenuTextArray)
{
	UE_LOG(LogTemp, Warning, TEXT("AMyCharacter::SetMenuTextArray"));
	MenuTextArray = NewMenuTextArray;
}

const TArray<FText>& AMyCharacter::GetMenuTextArray() const
{
	return MenuTextArray;
}

void AMyCharacter::ExamineItem(FName ItemName)
{
	KnownItemArray.Add(ItemName);
	InteractMenuIndex = 0;
	Cast<IInteractInterface>(CurrentInteractActor)->ShowInteractMenu(this);
}

AActor* AMyCharacter::GetInteractActor() const
{
	return CurrentInteractActor;
}

int AMyCharacter::GetInteractMenuIndex() const
{
	return InteractMenuIndex;
}

void AMyCharacter::CheckInteract()
{
	//UE_LOG(LogTemp, Warning, TEXT("AMyCharacter::CheckInteract : %s"), *GetName());
	if (UWorld* World = GetWorld())
	{
		FVector Start = FollowCamera->GetComponentLocation() + (CameraBoom->TargetArmLength * FollowCamera->GetForwardVector());
		FVector End = Start + CheckInteractLength * FollowCamera->GetForwardVector();
		FHitResult HitResult;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);
		if (World->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Camera, Params))
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
						}
						CurrentInteractActor = HitResult.GetActor();
						InteractMenuIndex = 0;
						Interface->ShowInteractMenu(this);
					}
					return;
				}
			}

		}
	}
	CurrentInteractActor = nullptr;
	MenuTextArray.Empty();
	if (HasAuthority())
	{
		if (AEscapePlayerController* PC = GetController<AEscapePlayerController>()) PC->HideInteractMenu();
	}
}

void AMyCharacter::DoInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("AMyCharacter::DoInteract"));
	Req_DoInteract();
}

void AMyCharacter::Req_DoInteract_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("AMyCharacter::Req_DoInteract_Implementation : InteractMenuIndex : %d"), InteractMenuIndex);
	if (IInteractInterface* Interface = Cast<IInteractInterface>(CurrentInteractActor)) Interface->Interact(this, MenuTextArray[InteractMenuIndex]);
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
	//UE_LOG(LogTemp, Warning, TEXT("AMyCharacter::MenuSelect : Value = %f"), WheelValue);
	if (CurrentInteractActor)
	{
		// Todo : 
		if (WheelValue > 0)
		{
			if (HasAuthority() && IsLocallyControlled())
			{
				InteractMenuIndex = InteractMenuIndex + 1 < MenuTextArray.Num() ? InteractMenuIndex + 1 : InteractMenuIndex;
				if (AEscapePlayerController* PC = GetController<AEscapePlayerController>())
				{
					PC->SelectMenu();
				}
			}
			else
			{
				Req_MenuSelectUp();
			}
		}
		else if (WheelValue < 0)
		{
			if (HasAuthority() && IsLocallyControlled())
			{
				InteractMenuIndex = InteractMenuIndex - 1 >= 0 ? InteractMenuIndex - 1 : InteractMenuIndex;
				if (AEscapePlayerController* PC = GetController<AEscapePlayerController>())
				{
					PC->SelectMenu();
				}
			}
			else
			{
				Req_MenuSelectDown();
			}
		}
		UE_LOG(LogTemp, Warning, TEXT("AMyCharacter::MenuSelect : InteractMenuIndex : %d"), InteractMenuIndex);
	}
}

void AMyCharacter::Req_MenuSelectUp_Implementation()
{
	if (MenuTextArray.Num())
	{
		InteractMenuIndex = InteractMenuIndex + 1 < MenuTextArray.Num() ? InteractMenuIndex + 1 : InteractMenuIndex;
		UE_LOG(LogTemp, Warning, TEXT("AMyCharacter::Req_MenuSelectUp : InteractMenuIndex = %d, MenuTextArrayNum = %d"), InteractMenuIndex, MenuTextArray.Num());
	}
}

void AMyCharacter::Req_MenuSelectDown_Implementation()
{
	if (MenuTextArray.Num() > 0)
	{
		InteractMenuIndex = InteractMenuIndex - 1 >= 0 ? InteractMenuIndex - 1 : InteractMenuIndex;
		UE_LOG(LogTemp, Warning, TEXT("AMyCharacter::Req_MenuSelectDown : InteractMenuIndex = %d"), InteractMenuIndex);
	}
}

void AMyCharacter::ToggleInGameMenu(const FInputActionValue& Value)
{
	// Todo :
	if (AEscapePlayerController* PC = GetController<AEscapePlayerController>())
	{
		PC->ToggleInGameMenu();
	}
}

void AMyCharacter::Aim(const FInputActionValue& Value)
{
	Req_Aim();
}

void AMyCharacter::Req_Aim_Implementation()
{
	if (bIsAimed) bIsAimed = false;
	else bIsAimed = true;
}

void AMyCharacter::OnRep_EscapeTime()
{
	if(IsLocallyControlled()) EscapeTimeDelegate.ExecuteIfBound(EscapeTime);
}

void AMyCharacter::OnRep_InteractMenuIndex()
{
	UE_LOG(LogTemp, Warning, TEXT("AMyCharacter::OnRep_InteractMenuIndex : InteractMenuIndex : %d"), InteractMenuIndex);
	if (AEscapePlayerController* PC = GetController<AEscapePlayerController>()) PC->SelectMenu();
}

void AMyCharacter::OnRep_MenuTextArray()
{
	if (AEscapePlayerController* PC = GetController<AEscapePlayerController>())
	{
		if (MenuTextArray.Num() == 0) PC->HideInteractMenu();
		else if (MenuTextArray.Num() > 0) PC->ShowInteractMenu();
	}
}

FText AMyCharacter::GetActorName()
{
	return FText::FromName(TEXT("시체"));
}