


#include "RunCharacterController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "RunCharacter.h"

void ARunCharacterController::BeginPlay()
{
	Super::BeginPlay();

	//add input mapping context
	if (APlayerController* PlayerController = Cast<APlayerController>(this))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}
/*
void ARunCharacterController::MoveForward(const FInputActionValue& Value)
{
	ARunCharacter* pawn = Cast<ARunCharacter>(GetPawn());

	if (pawn)
	{
		pawn->MoveForward(Value.Get<float>());
	}
}
*/
void ARunCharacterController::MoveRight(const FInputActionValue& Value)
{
	ARunCharacter* pawn = Cast<ARunCharacter>(GetPawn());

	if (pawn && !pawn->isDead)
	{
		pawn->MoveRight(Value.Get<float>());
	}
}

void ARunCharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//InputComponent
	APlayerController::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		//EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &ARunCharacterController::MoveForward);
		EnhancedInputComponent->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &ARunCharacterController::MoveRight);
	}
}

void ARunCharacterController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	ARunCharacter* pawn = Cast<ARunCharacter>(GetPawn());

	if (!pawn->isDead)
	{
		pawn->AddMovementInput(pawn->GetActorForwardVector());
	}
}
