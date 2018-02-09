// Fill out your copyright notice in the Description page of Project Settings.

#include "MySpawnpoint.h"
#include "MyEnemy.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Gruppe2_1GameModeBase.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

AMySpawnpoint::AMySpawnpoint()
{
	PrimaryActorTick.bCanEverTick = true;

	bSpawnTimerExpired = true;
	SpawnRate = 4.f;

//	MyGameMode = UGameplayStatics::GetGameMode;
}
void AMySpawnpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SpawnEnemy();
}

void AMySpawnpoint::SpawnEnemy() {
	if (bSpawnTimerExpired == true) {
		//if (MyGameMode) {
			const FRotator SpawnRotation = FRotator(0.f, 180.f, 0.f);

			const FVector SpawnLocation = GetActorLocation();

			UWorld* const World = GetWorld();
			if (World != NULL) {
				if (Enemy_BP != nullptr) {
					World->SpawnActor<AMyEnemy>(Enemy_BP, SpawnLocation, SpawnRotation);
				}
			}
			bSpawnTimerExpired = false;
			World->GetTimerManager().SetTimer(TimerHandle_SpawnTimerExpired, this, &AMySpawnpoint::SpawnTimerExpired, SpawnRate);
		}
//	}
}

void AMySpawnpoint::SpawnTimerExpired()
{
	bSpawnTimerExpired = true;
}
