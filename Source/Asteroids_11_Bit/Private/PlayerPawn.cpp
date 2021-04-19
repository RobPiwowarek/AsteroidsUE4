// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Asteroids_11_Bit/Asteroids_11_BitGameModeBase.h"
#include "Components/InputComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Camera/CameraComponent.h"
#include "Bullet.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>("PawnMovement");
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");;

	SetRootComponent(StaticMesh);
	CanShoot = true;
	SpaceBarHeld = false;
	level = 1;
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	GameMode = (class AAsteroids_11_BitGameModeBase*)GetWorld()->GetAuthGameMode();
}

void APlayerPawn::MoveHorizontal(float Amount)
{
	FloatingPawnMovement->AddInputVector(GetActorRightVector() * Amount);
}

void APlayerPawn::Shoot()
{
	SpaceBarHeld = true;
}

void APlayerPawn::AllowShoot()
{ 
	CanShoot = true;

	if (GameMode) {
		if (GameMode->Score <= 25) {
			level = 1;
		}
		else if (GameMode->Score <= 50) {
			level = 2;
		}
		else if (GameMode->Score <= 100) {
			level = 3;
		}
		else if (GameMode->Score <= 150) {
			level = 4;
		}
		else if (GameMode->Score > 150) {
			level = 5;
		}
	}

	GetWorldTimerManager().ClearTimer(ShootTimerHandle);
}

void APlayerPawn::ReleaseSpaceBar()
{
	SpaceBarHeld = false;
}

void APlayerPawn::SpawnBulletIfCanShoot()
{
	if (BulletClass) {
		if (CanShoot && SpaceBarHeld && ShotsPerSecond > 0.0f) {
			CanShoot = false;


			if (level == 1) {
				SpawnBulletAtLocation(GetActorLocation(), BulletClass);
			}
			else if (level == 2) {
				FVector location = GetActorLocation();

				SpawnBulletAtLocation(FVector(location.X - 50.0f, location.Y + 100.0f, location.Z), BulletClass);
				SpawnBulletAtLocation(FVector(location.X - 50.0f, location.Y - 100.0f, location.Z), BulletClass);
			}
			else if (level == 3) {
				FVector location = GetActorLocation();

				SpawnLevel4Bullets();
			}
			else if (level == 4) {
				SpawnLevel4Bullets();
				GetWorldTimerManager().SetTimer(Level4TimerHandle, this, &APlayerPawn::SpawnLevel4Bullets, 1 / (2*ShotsPerSecond), false);
			}
			else if (level >= 5) {
				SpawnLevel4Bullets();
				GetWorldTimerManager().SetTimer(Level4TimerHandle, this, &APlayerPawn::SpawnLevel5Bullets, 1 / (2 * ShotsPerSecond), false);
			}

			GetWorldTimerManager().SetTimer(ShootTimerHandle, this, &APlayerPawn::AllowShoot, 1 / ShotsPerSecond, false);
		}
	}
}

void APlayerPawn::SpawnBulletAtLocation(FVector location, TSubclassOf<class ABullet> bc)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.bNoFail = true;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = this;

	FTransform BulletSpawnTransform;
	BulletSpawnTransform.SetLocation(GetActorForwardVector() * 60.f + location);
	BulletSpawnTransform.SetRotation(GetActorRotation().Quaternion());
	BulletSpawnTransform.SetScale3D(FVector(0.25f));

	GetWorld()->SpawnActor<ABullet>(bc, BulletSpawnTransform, SpawnParams);

}

void APlayerPawn::SpawnLevel4Bullets()
{
	FVector location = GetActorLocation();

	SpawnBulletAtLocation(FVector(location.X - 50.0f, location.Y + 100.0f, location.Z), BulletClass);
	SpawnBulletAtLocation(FVector(location.X - 50.0f, location.Y - 100.0f, location.Z), BulletClass);
	SpawnBulletAtLocation(location, BulletClass);
}

void APlayerPawn::SpawnLevel5Bullets()
{
	FVector location = GetActorLocation();

	SpawnBulletAtLocation(FVector(location.X - 50.0f, location.Y + 100.0f, location.Z), Level5BulletClass);
	SpawnBulletAtLocation(FVector(location.X - 50.0f, location.Y - 100.0f, location.Z), Level5BulletClass);
	SpawnBulletAtLocation(location, Level5BulletClass);
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SpawnBulletIfCanShoot();
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis("MoveHorizontal", this, &APlayerPawn::MoveHorizontal);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &APlayerPawn::Shoot);
	PlayerInputComponent->BindAction("Shoot", IE_Released, this, &APlayerPawn::ReleaseSpaceBar);
}

