// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Asteroids_11_BitGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ASTEROIDS_11_BIT_API AAsteroids_11_BitGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	

	public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
		float Score = 0.0f;

};
