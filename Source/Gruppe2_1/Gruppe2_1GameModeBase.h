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
	UFUNCTION(BlueprintCallable, Category = "Enemies")
	void IncrementNumberOfEnemiesKilled() { NumberOfEnemiesKilled++; }
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Wave")
	bool GetUnlimitedWaves() { return bUnlimitedWaves; }
	
	UFUNCTION(BlueprintCallable, Category = "Wave")
	void SetUnlimitedWaves(bool UnlimitedWaves) { bUnlimitedWaves = UnlimitedWaves; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Wave")
	int GetWaveNumber() { return WaveNumber; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Wave")
	int GetMaxWaveNumber() { return MaxWaveNumber; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Enemy")
	int GetNumberOfEnemies() { return NumberOfEnemies; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Enemy")
	int GetMaxNumberOfEnemies() { return MaxNumberOfEnemiesThisWave; }
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Enemy")
	int GetNumberOfEnemiesKilled() { return NumberOfEnemiesKilled; }

private:

	AGruppe2_1GameModeBase();

	FTimerHandle TimerHandle_CanSpawnEnemy;
	
	TArray<AMyEnemy*> Enemies;

	TArray<AMySpawnpoint*> Spawnpoints;

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;
	
	void SpawnEnemies();

	void CheckIfNewWave();

	void ResetCanSpawnEnemy();

	int FindAllEnemies();

	int FindAllSpawnpoints();

	bool bCanSpawnEnemies;

	float SpawnRate;
	

	int NumberOfSpawnpoints;
	int NumberOfEnemiesSpawnedThisWave;
	
	bool bUnlimitedWaves;
	int WaveNumber;
	int MaxWaveNumber;
	
	int NumberOfEnemies;
	int NumberOfEnemiesKilled;
	int MaxNumberOfEnemiesThisWave;
};
