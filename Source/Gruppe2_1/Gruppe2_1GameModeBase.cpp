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
	bUnlimitedWaves = false;
	bTimerNotDone = true;

	SpawnRate = 1.50f;
	SpawnTimer = 60.f;
	NumberOfSpawnpoints = 0;
	SpawningModifier = 0.985f;

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
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_SetTimerDone, this, &AGruppe2_1GameModeBase::SetTimerDone, SpawnTimer); //TODO Hardcoded variabel!!

	if (bUnlimitedWaves)
	{
		MaxWaveNumber = WaveNumber;
	}
	UE_LOG(LogTemp, Warning, TEXT("Spawnrate is in BeginPlay: %d"), SpawnRate)
}

void AGruppe2_1GameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SpawnEnemies();
	
	TimerRemaining = GetWorld()->GetTimerManager().GetTimerRemaining(TimerHandle_SetTimerDone);

	NumberOfEnemies = FindAllEnemies();

}

//TODO Sette opp økende antall enemies per wave.
//TODO Sette opp en funksjon som kjører når du er ferdig med alle waves.
void AGruppe2_1GameModeBase::SpawnEnemies()
{
	if (bCanSpawnEnemies == true)
	{
		//if (WaveNumber <= MaxWaveNumber)
		//{
		//	MaxNumberOfEnemiesThisWave = 10 * WaveNumber * 1.2;
		//	if (NumberOfEnemiesSpawnedThisWave < MaxNumberOfEnemiesThisWave)
		//	{
		//	}
		//}
				int random = FMath::RandRange(0, NumberOfSpawnpoints - 1);
				Spawnpoints[random]->SpawnEnemy();
				FString TheFloatStr = FString::SanitizeFloat(SpawnRate);
				GEngine->AddOnScreenDebugMessage(-1, 1.0, FColor::Red, *TheFloatStr);
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
	//CheckIfNewWave();
}

void AGruppe2_1GameModeBase::SpawnEnemiesTimeBased()
{
	if (bCanSpawnEnemies == true)
	{
		if (bTimerNotDone == true)
		{
			int random = FMath::RandRange(0, NumberOfSpawnpoints - 1);
			Spawnpoints[random]->SpawnEnemy();
			bCanSpawnEnemies = false;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle_ResetCanSpawnEnemy, this, &AGruppe2_1GameModeBase::ResetCanSpawnEnemy, SpawnRate);
		}
	}
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

void AGruppe2_1GameModeBase::SetTimerDone()
{
	bTimerNotDone = false;
}
