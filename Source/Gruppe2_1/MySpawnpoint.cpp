// Fill out your copyright notice in the Description page of Project Settings.

#include "MySpawnpoint.h"
#include "MyEnemy.h"
#include "Engine/World.h"
#include "TimerManager.h"

AMySpawnpoint::AMySpawnpoint()
{
	PrimaryActorTick.bCanEverTick = true;

	bCanSpawn = true;
	SpawnRate = 4.f;
}
void AMySpawnpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SpawnEnemy();
}

void AMySpawnpoint::SpawnEnemy() {
	if (bCanSpawn == true) {
		const FRotator SpawnRotation = FRotator(0.f, 180.f, 0.f);

		const FVector SpawnLocation = GetActorLocation();

		UWorld* const World = GetWorld();
		if (World != NULL) {
			if (Enemy_BP != nullptr) {
				World->SpawnActor<AMyEnemy>(Enemy_BP, SpawnLocation, SpawnRotation);
			}
		}
		bCanSpawn = false;
		World->GetTimerManager().SetTimer(TimerHandle_SpawnTimerExpired, this, &AMySpawnpoint::SpawnTimerExpired, SpawnRate);
	}
}

void AMySpawnpoint::SpawnTimerExpired()
{
	bCanSpawn = true;
}
