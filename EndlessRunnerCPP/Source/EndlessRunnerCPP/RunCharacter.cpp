// Fill out your copyright notice in the Description page of Project Settings.


#include "RunCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "RunCharacterController.h"

// Sets default values
ARunCharacter::ARunCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");

	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void ARunCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	isDead = false;
}

void ARunCharacter::MoveForward(float value)
{
	FVector currentLocation = GetActorLocation();
	FVector move = GetActorForwardVector() * value;

	AddMovementInput(move);
}

void ARunCharacter::MoveRight(float value)
{
	FVector currentLocation = GetActorLocation();
	FVector move = GetActorRightVector() * value;

	AddMovementInput(move);
}

void ARunCharacter::Die()
{
	OnDeath.Broadcast(this);
	isDead = true;
	//GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor::Red, "Player death");

	if (isDead)
	{
		// disable input
		DisableInput(Cast<APlayerController>(GetController()));

	}
}

void ARunCharacter::AddCoin()
{
	playerCoins += 1;
	//GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor::Yellow, "COINS");
}

// Called every frame
void ARunCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARunCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

