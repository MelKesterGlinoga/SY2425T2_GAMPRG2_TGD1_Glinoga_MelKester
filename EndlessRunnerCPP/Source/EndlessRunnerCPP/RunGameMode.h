// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RunGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNERCPP_API ARunGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	

protected:
	virtual void BeginPlay() override;
	/*
	UPROPERTY(VisibleAnywhere)
	class AFloorTile* FloorTile;
	*/
	UPROPERTY(EditAnywhere, Category = "Reference to Class")
	class TSubclassOf<class AFloorTile> BPTile;
	
	UPROPERTY(VisibleAnywhere)
	class ARunCharacter* RunCharacter;
	
	UPROPERTY(VisibleAnywhere)
	FTransform AttachPoint;

	UFUNCTION()
	void SpawnTile();

	UFUNCTION()
	void OnExit(AActor* Tile);

	UFUNCTION()
	void DestroyTile(AFloorTile* PreviousTile);

	UFUNCTION(BlueprintImplementableEvent)
	void RestartLevel(ARunCharacter* RunChar);
};
