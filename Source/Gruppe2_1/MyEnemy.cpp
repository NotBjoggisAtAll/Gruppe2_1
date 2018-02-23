// Fill out your copyright notice in the Description page of Project Settings.

#include "MyEnemy.h"
#include "Gruppe2_1GameModeBase.h"
#include "Projectile.h"

// Sets default values
AMyEnemy::AMyEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AMyEnemy::GetEnemyDeathLocation()
{
	
}

// Called when the game starts or when spawned
void AMyEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
void AMyEnemy::Destroyed() {

	Super::Destroyed();

	// Get World
	UWorld* World = GetWorld();

	if (World)
	{
		// Game mode 
		AGruppe2_1GameModeBase* MyGameMode = Cast<AGruppe2_1GameModeBase>(World->GetAuthGameMode());
		if (MyGameMode)
		{
			MyGameMode->IncrementNumberOfEnemiesKilled();
		}
	}
}

