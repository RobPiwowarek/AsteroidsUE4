// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

UCLASS()
class ASTEROIDS_11_BIT_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

	UPROPERTY(EditAnywhere, Category = "Attack")
		float ShotsPerSecond;


protected:
	bool CanShoot;
	bool SpaceBarHeld;
	int level;
	FTimerHandle ShootTimerHandle;
	FTimerHandle Level4TimerHandle;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveHorizontal(float Amount);
	void Shoot();
	void AllowShoot();
	void ReleaseSpaceBar(); 
	void SpawnBulletIfCanShoot();
	void SpawnLevel4Bullets();
	void SpawnLevel5Bullets();
	void SpawnBulletAtLocation(FVector location, TSubclassOf<class ABullet> bulletClass);

    class UFloatingPawnMovement* FloatingPawnMovement;
	class AAsteroids_11_BitGameModeBase*GameMode;

	UPROPERTY(EditAnywhere, Category = "Components")
	    UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, Category = "Components")
		class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Shooting")
		TSubclassOf<class ABullet> BulletClass;

	UPROPERTY(EditAnywhere, Category = "Shooting")
		TSubclassOf<class ABullet> Level5BulletClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
