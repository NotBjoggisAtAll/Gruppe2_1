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

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	void IncrementNumberOfEnemiesKilled() { NumberOfEnemiesKilled++; }
	
	//Getters
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Wave")
	bool GetUnlimitedWaves() const { return bUnlimitedWaves; }
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Wave")
	int GetWaveNumber() const { return WaveNumber; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Wave")
	int GetMaxWaveNumber() const { return MaxWaveNumber; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Enemy")
	int GetNumberOfEnemies() const { return NumberOfEnemies; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Enemy")
	int GetMaxNumberOfEnemies() const { return MaxNumberOfEnemiesThisWave; }
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Enemy")
	int GetNumberOfEnemiesKilled() { return NumberOfEnemiesKilled; }

	//Setters

	UFUNCTION(BlueprintCallable, Category = "Wave")
	void SetUnlimitedWaves(bool UnlimitedWaves) { bUnlimitedWaves = UnlimitedWaves; }

protected:

	//Functions
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

	void SpawnEnemies();

	void CheckIfNewWave();
	
	int FindAllEnemies();

	int FindAllSpawnpoints();

	//Timers

	FTimerHandle TimerHandle_ResetCanSpawnEnemy;
	
	void ResetCanSpawnEnemy();
	
	//Variables

	bool bCanSpawnEnemies;
	bool bUnlimitedWaves;

	float SpawnRate;

	int NumberOfSpawnpoints;
	int WaveNumber;
	int MaxWaveNumber;
	int NumberOfEnemies;
	int NumberOfEnemiesSpawnedThisWave;
	int MaxNumberOfEnemiesThisWave;
	int NumberOfEnemiesKilled;
	
	TArray<AMyEnemy*> Enemies;
	TArray<AMySpawnpoint*> Spawnpoints;
};