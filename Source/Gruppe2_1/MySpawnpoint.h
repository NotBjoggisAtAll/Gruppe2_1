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
public:

	UPROPERTY(EditAnywhere)
	TSubclassOf<AMyEnemy> Enemy_1;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AMyEnemy> Enemy_2;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AMyEnemy> Enemy_3;

	AMySpawnpoint();

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void SpawnEnemy();
};
