// Fill out your copyright notice in the Description page of Project Settings.


#include "ColliderActor.h"
#include "Components/BoxComponent.h"

// Sets default values
AColliderActor::AColliderActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("Box Component");
	
	SetRootComponent(BoxComponent);
}

// Called when the game starts or when spawned
void AColliderActor::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AColliderActor::Anything); // OnOverlapComponent
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AColliderActor::AnythingEnd); //OnOverlapEnd

	OnCollision.AddDynamic(this, &AColliderActor::CustomOnColl);
}

void AColliderActor::Anything(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor::Red, "Hello World");
	}

	OnCollision.Broadcast(this);
}

void AColliderActor::AnythingEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor::Red, "Byebye World");
	}
}

void AColliderActor::CustomOnColl(AActor* TestActor)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor::Yellow, "Custom worked");
	}
}

// Called every frame
void AColliderActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}