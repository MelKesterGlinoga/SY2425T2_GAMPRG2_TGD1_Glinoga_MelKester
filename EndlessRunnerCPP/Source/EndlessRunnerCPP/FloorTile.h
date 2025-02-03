// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorTile.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerExit, AActor*, Tile);

UCLASS()
class ENDLESSRUNNERCPP_API AFloorTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloorTile();

	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere)
	class UArrowComponent* AttachPoint;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxCollision;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* ObstacleSpawn;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* PickupSpawn;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void OnPlayerExit(UPrimitiveComponent* OverlappedComponent,
						AActor* OtherActor,
						UPrimitiveComponent* OtherComp, int32
						OtherBodyIndex,
						bool bFromSweep,
						const FHitResult& SweepResult);

	UFUNCTION()
	virtual FTransform GetAttachTransform();

	UFUNCTION()
	void SpawnObstacle();

	UFUNCTION()
	void SpawnPickup();

	UFUNCTION()
	void DestroyObjects();

	UPROPERTY(EditAnywhere, Category = "Obstacle References")
	TArray<TSubclassOf<class AObstacle>> BPObstacle;

	UPROPERTY()
	TArray<class AObstacle*> ObstacleSpawned;

	UPROPERTY(EditAnywhere, Category = "Pickup References")
	TArray<TSubclassOf<class APickup>> BPPickup;

	UPROPERTY()
	TArray<class APickup*> PickupSpawned;

	UPROPERTY(EditAnywhere)
	int32 PickupSpawnCount = 3;

	UPROPERTY(BlueprintAssignable)
	FOnPlayerExit Exited;

	UPROPERTY()
	FVector transformVec;
};
