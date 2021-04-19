// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AsteroidSpawner.generated.h"

UCLASS()
class ASTEROIDS_11_BIT_API AAsteroidSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAsteroidSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	float MinY;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	float MaxY;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	float AsteroidsPerSecond;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	float AsteroidsIncreasePerSecond;

	UPROPERTY(EditAnywhere, Category = "Spawn")
		TSubclassOf<AActor> AsteroidClass;

	FTimerHandle AsteroidSpawnTimerHandle;
	FTimerHandle FrequencyIncreaseTimerHandle;

	void HandleSpawn();

	void HandleFrequencyIncrease();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
