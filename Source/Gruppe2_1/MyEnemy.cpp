// Fill out your copyright notice in the Description page of Project Settings.

#include "MyEnemy.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Gruppe2_1GameModeBase.h"
#include "Classes/Particles/ParticleEmitter.h"
#include "Projectile.h"
#include "MyCharacter.h"

// Sets default values
AMyEnemy::AMyEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Strength = 1.f;

	PSC = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MyPSC"));
	PSC->SetupAttachment(RootComponent);
	GetParticles = 10;

}

// Called when the game starts or when spawned
void AMyEnemy::BeginPlay()
{
	Super::BeginPlay();
	PSC->Activate();
}

// Called every frame
void AMyEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GotHit == true)
	{
		GetParticles = PSC->GetNumActiveParticles();
		if (GetParticles == 0)
		{
			Destroy();
		}
	}
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
void AMyEnemy::GetDestroyed()
{
	GotHit = true;
	PSC->Deactivate();
	SetActorEnableCollision(false);
	GetMesh()->SetHiddenInGame(true);
}