// Fill out your copyright notice in the Description page of Project Settings.

#include "Gruppe2_1GameModeBase.h"
#include "EngineUtils.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "MySpawnpoint.h"
#include "MyEnemy.h"
#include "Engine.h"

AGruppe2_1GameModeBase::AGruppe2_1GameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;

	bCanSpawnEnemies = true;

	SpawnRate = 1.50f;
	NumberOfSpawnpoints = 0;
	SpawningModifier = 0.985f;

	NumberOfEnemies = 0;
	NumberOfEnemiesSpawned = 0;
	NumberOfEnemiesKilled = 0;
}

void AGruppe2_1GameModeBase::BeginPlay()
{
	Super::BeginPlay();

	NumberOfSpawnpoints = FindAllSpawnpoints();
	
}

void AGruppe2_1GameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SpawnEnemies();

	NumberOfEnemies = FindAllEnemies();
}

void AGruppe2_1GameModeBase::SpawnEnemies()
{
	if (bCanSpawnEnemies == true)
	{
		if (NumberOfEnemiesKilled < 50) {
			int random = FMath::RandRange(0, NumberOfSpawnpoints - 1);
			Spawnpoints[random]->SpawnEnemy();
			FString TheFloatStr = FString::SanitizeFloat(SpawnRate);
			//GEngine->AddOnScreenDebugMessage(-1, 1.0, FColor::Red, *TheFloatStr);
			bCanSpawnEnemies = false;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle_ResetCanSpawnEnemy, this, &AGruppe2_1GameModeBase::ResetCanSpawnEnemy, SpawnRate);
			if (SpawnRate < 0.8f)
			{
				SpawnRate = 0.8f;
			}
			else
			{
				SpawnRate = SpawnRate * SpawningModifier;
			}
		}
		else 
		{
			bNextLevel = true;
		}
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
	NumberOfEnemiesSpawned++;
}