// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "MySpawnpoint.generated.h"

/**
*
*/
class AMyEnemy;

UCLASS()
class GRUPPE2_1_API AMySpawnpoint : public ATargetPoint
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere)
		TSubclassOf<AMyEnemy> Enemy_BP;

public:

	AMySpawnpoint();

	virtual void Tick(float DeltaTime) override;

	void SpawnEnemy();

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		bool bCanSpawn;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float SpawnRate;

	void SpawnTimerExpired();

	/** Handle for efficient management of ShotTimerExpired timer */
	FTimerHandle TimerHandle_SpawnTimerExpired;
};
