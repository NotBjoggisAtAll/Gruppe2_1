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

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Level")
	bool GetNextLevel() const { return bNextLevel; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Enemy")
	int GetNumberOfEnemies() const { return NumberOfEnemies; }
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Enemy")
	int GetNumberOfEnemiesKilled() { return NumberOfEnemiesKilled; }

protected:

	//Functions
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

	void SpawnEnemies();
	
	int FindAllEnemies();

	int FindAllSpawnpoints();

	//Timers

	FTimerHandle TimerHandle_ResetCanSpawnEnemy;
	void ResetCanSpawnEnemy();

	//Variables

	bool bCanSpawnEnemies;
	bool bUnlimitedWaves;
	bool bTimerNotDone;
	bool bNextLevel;

	float SpawnRate;
	float SpawnTimer;
	float TimerRemaining;
	float SpawningModifier;

	int NumberOfSpawnpoints;
	int NumberOfEnemies;
	int NumberOfEnemiesSpawned;
	int NumberOfEnemiesKilled;
	
	TArray<AMyEnemy*> Enemies;
	TArray<AMySpawnpoint*> Spawnpoints;
};