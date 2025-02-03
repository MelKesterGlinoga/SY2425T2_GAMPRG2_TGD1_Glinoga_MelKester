// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorTile.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "RunCharacter.h"
#include "RunGameMode.h"
#include "Obstacle.h"
#include "Pickup.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AFloorTile::AFloorTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Floor");
	AttachPoint = CreateDefaultSubobject<UArrowComponent>("AttachPoint");
	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	ObstacleSpawn = CreateDefaultSubobject<UBoxComponent>("ObstacleArea");
	PickupSpawn = CreateDefaultSubobject<UBoxComponent>("PickupArea");

	SetRootComponent(SceneComponent);
	StaticMesh->SetupAttachment(SceneComponent);
	AttachPoint->SetupAttachment(SceneComponent);
	BoxCollision->SetupAttachment(SceneComponent);
	ObstacleSpawn->SetupAttachment(SceneComponent);
	PickupSpawn->SetupAttachment(SceneComponent);
}

// Called when the game starts or when spawned
void AFloorTile::BeginPlay()
{
	Super::BeginPlay();
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AFloorTile::OnPlayerExit);
	
	if (UKismetMathLibrary::RandomBoolWithWeight(0.2f))
	{
		for (int i = 0; i < PickupSpawnCount; i++)
		{
			SpawnPickup();
		}
	}
	else if (UKismetMathLibrary::RandomBoolWithWeight(0.5))
	{
		SpawnObstacle();
	}
}

void AFloorTile::OnPlayerExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ARunCharacter* RunCharacter = Cast<ARunCharacter>(OtherActor))
	{
		Exited.Broadcast(this);

		// set timer for destroying objects
		FTimerHandle DestroyObjectsTimerHandle;
		FTimerDelegate ObjectsDelegate;
		ObjectsDelegate.BindUFunction(this, "DestroyObjects");

		// set timer via getworld
		GetWorldTimerManager().SetTimer(DestroyObjectsTimerHandle, ObjectsDelegate, 1.0f, false);
	}
}

FTransform AFloorTile::GetAttachTransform()
{
	return AttachPoint->GetComponentTransform();
}

void AFloorTile::SpawnObstacle()
{
	FTransform ObstacleSpawnTransform = (FTransform)UKismetMathLibrary::RandomPointInBoundingBox(transformVec, ObstacleSpawn->GetScaledBoxExtent());
	AObstacle* Obstacle = GetWorld()->SpawnActor<AObstacle>(BPObstacle[0], ObstacleSpawnTransform);
	Obstacle->AttachToComponent(ObstacleSpawn, FAttachmentTransformRules::KeepRelativeTransform);
	ObstacleSpawned.Add(Obstacle);
}

void AFloorTile::SpawnPickup()
{
	FTransform PickupSpawnTransform = (FTransform)UKismetMathLibrary::RandomPointInBoundingBox(transformVec, PickupSpawn->GetScaledBoxExtent());
	APickup* Pickup = GetWorld()->SpawnActor<APickup>(BPPickup[0], PickupSpawnTransform);
	Pickup->AttachToComponent(ObstacleSpawn, FAttachmentTransformRules::KeepRelativeTransform);
	PickupSpawned.Add(Pickup);
}

void AFloorTile::DestroyObjects()
{
	// foreach loop 
	// destroy the objects
	for (AObstacle* Obstacle : ObstacleSpawned)
	{
		Obstacle->Destroy();
	}
	for (APickup* Pickup : PickupSpawned)
	{
		Pickup->Destroy();
	}
}

// Called every frame
void AFloorTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}