// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "MySpawnpoint.generated.h"

/**
*
*/
class AMyEnemy;
class AGruppe2_1_GameModeBase;

UCLASS()
class GRUPPE2_1_API AMySpawnpoint : public ATargetPoint
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<AMyEnemy> Enemy_BP;

	UPROPERTY(EditAnywhere)
	bool bCanSpawn;

	//AGruppe2_1_GameModeBase*  MyGameMode;
	

public:

	AMySpawnpoint();

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	float SpawnRate;

protected:

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(Category = Gameplay, BlueprintReadOnly)
	bool bSpawnTimerExpired;

private:

	void SpawnEnemy();
	void SpawnTimerExpired();

	/** Handle for efficient management of ShotTimerExpired timer */
	FTimerHandle TimerHandle_SpawnTimerExpired;
};
