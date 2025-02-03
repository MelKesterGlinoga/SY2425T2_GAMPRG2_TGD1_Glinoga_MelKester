// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "RunCharacterController.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNERCPP_API ARunCharacterController : public APlayerController
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere)
	class UInputAction* MoveForwardAction;

	UPROPERTY(EditAnywhere)
	class UInputAction* MoveRightAction;

	//UPROPERTY()
	//bool isAlive;

protected:
	virtual void BeginPlay() override;

	//UFUNCTION()
	//void MoveForward(const FInputActionValue& Value);

	UFUNCTION()
	void MoveRight(const FInputActionValue& Value);

	virtual void SetupInputComponent() override;

	virtual void Tick(float DeltaSeconds) override;
};
