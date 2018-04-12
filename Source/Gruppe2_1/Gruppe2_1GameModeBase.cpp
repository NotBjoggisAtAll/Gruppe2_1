// Fill out your copyright notice in the Description page of Project Settings.

#include "Gruppe2_1GameModeBase.h"
#include "EngineUtils.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "MySpawnpoint.h"
#include "MyEnemy.h"

AGruppe2_1GameModeBase::AGruppe2_1GameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;

	bCanSpawnEnemies = true;
	bUnlimitedWaves = false;

	SpawnRate = 1.f;
	
	NumberOfSpawnpoints = 0;

	WaveNumber = 1;
	MaxWaveNumber = 3;
	NumberOfEnemies = 0;
	NumberOfEnemiesSpawnedThisWave = 0;
	MaxNumberOfEnemiesThisWave = 10;
	NumberOfEnemiesKilled = 0;
}

void AGruppe2_1GameModeBase::BeginPlay()
{
	Super::BeginPlay();

	NumberOfSpawnpoints = FindAllSpawnpoints();

	if (bUnlimitedWaves)
	{
		MaxWaveNumber = WaveNumber;
	}
}

void AGruppe2_1GameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SpawnEnemies();
	
	NumberOfEnemies = FindAllEnemies();

}

//TODO Sette opp økende antall enemies per wave.
//TODO Sette opp en funksjon som kjører når du er ferdig med alle waves.
void AGruppe2_1GameModeBase::SpawnEnemies()
{
	if (bCanSpawnEnemies == true)
	{
		if (WaveNumber <= MaxWaveNumber)
		{
			if (NumberOfEnemiesSpawnedThisWave < MaxNumberOfEnemiesThisWave)
			{
				UWorld* World = GetWorld();
				int random = FMath::RandRange(0, NumberOfSpawnpoints - 1);
				Spawnpoints[random]->SpawnEnemy();
				bCanSpawnEnemies = false;
				World->GetTimerManager().SetTimer(TimerHandle_ResetCanSpawnEnemy, this, &AGruppe2_1GameModeBase::ResetCanSpawnEnemy, SpawnRate);
			}
		}
	}
	CheckIfNewWave();
}

void AGruppe2_1GameModeBase::CheckIfNewWave()
{
	if ((NumberOfEnemiesSpawnedThisWave == MaxNumberOfEnemiesThisWave) && NumberOfEnemies == 0)
	{
		WaveNumber++;
		NumberOfEnemiesSpawnedThisWave = 0;
	}
}

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

void AGruppe2_1GameModeBase::ResetCanSpawnEnemy() 
{
	bCanSpawnEnemies = true;
	NumberOfEnemiesSpawnedThisWave++;
}