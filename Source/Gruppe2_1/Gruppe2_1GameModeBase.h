// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Gruppe2_1GameModeBase.generated.h"

class AMyEnemy;
class AMySpawnpoint;

UCLASS()
class GRUPPE2_1_API AGruppe2_1GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	AGruppe2_1GameModeBase();

	TArray<AMyEnemy*> Enemies;
	TArray<AMySpawnpoint*> Spawnpoints;

	UPROPERTY(BlueprintReadWrite, Category = "Enemies")
	bool bCanSpawnEnemies;
	
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	int GetWaveNumber() { return WaveNumber; }

	UFUNCTION(BlueprintCallable, Category = "Enemies")
		int GetNumberOfEnemies() { return NumberOfEnemies; }

	UFUNCTION(BlueprintCallable, Category = "Enemies")
		int GetMaxNumberOfEnemies() { return MaxNumberOfEnemies; }

	UFUNCTION(BlueprintCallable, Category = "Enemies")
	int GetNumberOfEnemiesKilled() { return NumberOfEnemiesKilled; }

	UFUNCTION(BlueprintCallable, Category = "Enemies")
		void IncrementNumberOfEnemiesKilled() { NumberOfEnemiesKilled++; }

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void SpawnEnemies();

	void CheckIfNewWave();

	void ResetCanSpawnEnemy();

protected:

	FTimerHandle TimerHandle_CanSpawnEnemy;

	int FindAllEnemies();
	
	int FindAllSpawnpoints();

	int NumberOfSpawnpoints;
	float SpawnRate;

	int counter;

	int WaveNumber;
	int MaxWave;

	int NumberOfEnemies;
	int MaxNumberOfEnemies;
	int NumberOfEnemiesKilled;

};
