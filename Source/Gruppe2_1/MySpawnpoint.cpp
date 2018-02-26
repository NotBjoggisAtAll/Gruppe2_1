// Fill out your copyright notice in the Description page of Project Settings.

#include "MySpawnpoint.h"
#include "MyEnemy.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Math/UnrealMathUtility.h"

AMySpawnpoint::AMySpawnpoint()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AMySpawnpoint::SpawnEnemy() {
	UWorld* const World = GetWorld();
	
	const FRotator SpawnRotation = FRotator(0.f, 180.f, 0.f);
	const FVector SpawnLocation = GetActorLocation();

	int RandomEnemy = FMath::RandRange(1, 3);
	
	if (World != NULL) {
		switch (RandomEnemy)
		{
		case 1:
			if (Enemy_1 != nullptr) {
				World->SpawnActor<AMyEnemy>(Enemy_1, SpawnLocation, SpawnRotation);
			}
			break;
		case 2:
			if (Enemy_2 != nullptr) {
				World->SpawnActor<AMyEnemy>(Enemy_2, SpawnLocation, SpawnRotation);
			}
			break;
		case 3:
			if (Enemy_3 != nullptr) {
				World->SpawnActor<AMyEnemy>(Enemy_3, SpawnLocation, SpawnRotation);
			}
			break;
		default:
			break;
		}
	}
}
