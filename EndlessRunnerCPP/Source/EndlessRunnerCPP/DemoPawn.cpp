// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoPawn.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ADemoPawn::ADemoPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("DemoPawnStaticMesh");
}

// Called when the game starts or when spawned
void ADemoPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADemoPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADemoPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

