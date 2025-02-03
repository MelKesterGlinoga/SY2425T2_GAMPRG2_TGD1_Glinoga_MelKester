// Fill out your copyright notice in the Description page of Project Settings.


#include "RunGameMode.h"
#include "FloorTile.h"
#include "RunCharacter.h"
#include "Kismet/GameplayStatics.h"

void ARunGameMode::BeginPlay()
{
	Super::BeginPlay();

	SpawnTile();
	
	for (int i = 0; i < 8; i++)
	{
		SpawnTile();
	}

	RunCharacter = Cast<ARunCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetCharacter());
	// listen to OnDeath; restarts the level
	RunCharacter->OnDeath.AddDynamic(this, &ARunGameMode::RestartLevel);
}

void ARunGameMode::SpawnTile()
{
	AFloorTile* Tile = GetWorld()->SpawnActor<AFloorTile>(BPTile, AttachPoint);
	AttachPoint = Tile->GetAttachTransform();
	//GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor::Red, "Hello World");

	Tile->Exited.AddDynamic(this, &ARunGameMode::OnExit);
}

void ARunGameMode::OnExit(AActor* Tile)
{
	SpawnTile();
	
	/*
	Delay to destroy tile
	https://www.tomlooman.com/unreal-engine-cpp-timers/
	*/
	FTimerHandle DestroyTileTimerHandle;
	FTimerDelegate Delegate;
	Delegate.BindUFunction(this, "DestroyTile", Tile);

	// set timer via getworld
	GetWorldTimerManager().SetTimer(DestroyTileTimerHandle, Delegate, 1.0f, false);
}

void ARunGameMode::DestroyTile(AFloorTile* PreviousTile)
{
	PreviousTile->Destroy();
}
