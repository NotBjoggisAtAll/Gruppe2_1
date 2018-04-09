// Fill out your copyright notice in the Description page of Project Settings.

#include "Gruppe2_1GameModeBase.h"
#include "EngineUtils.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "MySpawnpoint.h"
#include "MyEnemy.h"

AGruppe2_1GameModeBase::AGruppe2_1GameModeBase() {
	PrimaryActorTick.bCanEverTick = true;

	bCanSpawnEnemies = true;
	SpawnRate = 1.f;
	NumberOfEnemiesSpawnedThisWave = 0;

	WaveNumber = 1;
	MaxWaveNumber = 3;

	MaxNumberOfEnemies = 10;
	NumberOfEnemies = 0;
	NumberOfEnemiesKilled = 0;
}

// Finds all enemies, adds them to the array and return the number
int AGruppe2_1GameModeBase::FindAllEnemies()
{
	int temp = 0;
	for (TActorIterator<AMyEnemy> It(GetWorld(), AMyEnemy::StaticClass()); It; ++It)
	{
		AMyEnemy* Enemy = Cast<AMyEnemy>(*It);
		Enemies.Add(Enemy);
		temp++;
	}
	return temp;
}

int AGruppe2_1GameModeBase::FindAllSpawnpoints()
{
	int temp = 0;
	for (TActorIterator<AMySpawnpoint> It(GetWorld(), AMySpawnpoint::StaticClass()); It; ++It)
	{
		AMySpawnpoint* Spawnpoint = Cast<AMySpawnpoint>(*It);
		Spawnpoints.Add(Spawnpoint);
		temp++;
	}
	return temp;
}

void AGruppe2_1GameModeBase::BeginPlay()
{
	Super::BeginPlay();

	NumberOfSpawnpoints = FindAllSpawnpoints();
}

void AGruppe2_1GameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bUnlimitedWaves) {
		MaxWaveNumber = WaveNumber;
	}
	SpawnEnemies();
	
	NumberOfEnemies = FindAllEnemies();

}

void AGruppe2_1GameModeBase::SpawnEnemies()
{
	if (bCanSpawnEnemies == true) {
		if (WaveNumber <= MaxWaveNumber) {
			if (NumberOfEnemiesSpawnedThisWave < MaxNumberOfEnemies) {
				UWorld* World = GetWorld();
				int random = FMath::RandRange(0, NumberOfSpawnpoints - 1);
				Spawnpoints[random]->SpawnEnemy();
				bCanSpawnEnemies = false;
				World->GetTimerManager().SetTimer(TimerHandle_CanSpawnEnemy, this, &AGruppe2_1GameModeBase::ResetCanSpawnEnemy, SpawnRate);
			}
		}
	}
	CheckIfNewWave();
}

void AGruppe2_1GameModeBase::CheckIfNewWave()
{
	if ((NumberOfEnemiesSpawnedThisWave == MaxNumberOfEnemies) && NumberOfEnemies == 0)
	{
		WaveNumber++;
		NumberOfEnemiesSpawnedThisWave = 0;
	}
}

void AGruppe2_1GameModeBase::ResetCanSpawnEnemy() 
{
	bCanSpawnEnemies = true;
	NumberOfEnemiesSpawnedThisWave++;
}