// Fill out your copyright notice in the Description page of Project Settings.


#include "AsteroidSpawner.h"

// Sets default values
AAsteroidSpawner::AAsteroidSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAsteroidSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(AsteroidSpawnTimerHandle, this, &AAsteroidSpawner::HandleSpawn, 1 / AsteroidsPerSecond, false);
	GetWorldTimerManager().SetTimer(FrequencyIncreaseTimerHandle, this, &AAsteroidSpawner::HandleFrequencyIncrease, 1.0f, false);
}

void AAsteroidSpawner::HandleSpawn()
{

	if (AsteroidClass) {
		if (AsteroidsIncreasePerSecond > 0.0f) {
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			SpawnParams.bNoFail = true;
			SpawnParams.Owner = this;

			FTransform AsteroidSpawnTransform;
			FVector location = GetActorLocation();
			float y = FMath::RandRange(MinY, MaxY);

			AsteroidSpawnTransform.SetLocation(GetActorForwardVector() + FVector(location.X, y, location.Z));
			AsteroidSpawnTransform.SetRotation(GetActorRotation().Quaternion());

			GetWorld()->SpawnActor<AActor>(AsteroidClass, AsteroidSpawnTransform, SpawnParams);

			GetWorldTimerManager().ClearTimer(AsteroidSpawnTimerHandle);

			GetWorldTimerManager().SetTimer(AsteroidSpawnTimerHandle, this, &AAsteroidSpawner::HandleSpawn, 1 / AsteroidsPerSecond, false);
		}
	}

}

void AAsteroidSpawner::HandleFrequencyIncrease()
{
	AsteroidsPerSecond += AsteroidsIncreasePerSecond;
	
	GetWorldTimerManager().ClearTimer(FrequencyIncreaseTimerHandle);
}

// Called every frame
void AAsteroidSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

