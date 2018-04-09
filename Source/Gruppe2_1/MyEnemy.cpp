// Fill out your copyright notice in the Description page of Project Settings.

#include "MyEnemy.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Gruppe2_1GameModeBase.h"
#include "Projectile.h"
#include "MyCharacter.h"

// Sets default values
AMyEnemy::AMyEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Strength = 1.f;
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

	UWorld* World = GetWorld();

	if (World)
	{
		AGruppe2_1GameModeBase* MyGameMode = Cast<AGruppe2_1GameModeBase>(World->GetAuthGameMode());
		if (MyGameMode)
		{
			MyGameMode->IncrementNumberOfEnemiesKilled();
		}
	}
}