// Fill out your copyright notice in the Description page of Project Settings.

#include "MySpawnpoint.h"
#include "MyEnemy.h"
#include "Engine/World.h"
#include "TimerManager.h"

AMySpawnpoint::AMySpawnpoint()
{
	//PrimaryActorTick.bCanEverTick = true; //Tick trengs ikke da spawning nå styres av MyGameMode

	//bSpawnTimerExpired = true; 		//Timer flyttet til MyGameMode_BP
	//SpawnRate = 4.f; 		//Timer flyttet til MyGameMode_BP

}
//void AMySpawnpoint::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//	//SpawnEnemy(); // Spawning styres nå av MyGameMode_BP
//}

void AMySpawnpoint::SpawnEnemy() {
	//if (bSpawnTimerExpired == true) {
		const FRotator SpawnRotation = FRotator(0.f, 180.f, 0.f);

		const FVector SpawnLocation = GetActorLocation();

		UWorld* const World = GetWorld();
		if (World != NULL) {
			if (Enemy_BP != nullptr) {
				World->SpawnActor<AMyEnemy>(Enemy_BP, SpawnLocation, SpawnRotation);
			}
		}
		//Timer flyttet til MyGameMode_BP
	 // bSpawnTimerExpired = false;
	//	World->GetTimerManager().SetTimer(TimerHandle_SpawnTimerExpired, this, &AMySpawnpoint::SpawnTimerExpired, SpawnRate);
	//}
}
//Timer flyttet til MyGameMode_BP
//void AMySpawnpoint::SpawnTimerExpired()
//{
//	bSpawnTimerExpired = true;
//}
