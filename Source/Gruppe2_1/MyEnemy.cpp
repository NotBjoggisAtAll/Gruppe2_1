// Fill out your copyright notice in the Description page of Project Settings.

#include "MyEnemy.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Gruppe2_1GameModeBase.h"
#include "Classes/Particles/ParticleEmitter.h"
#include "Projectile.h"
#include "MyCharacter.h"

AMyEnemy::AMyEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	Strength = 1.f;

	PSC = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MyPSC"));
	PSC->SetupAttachment(RootComponent);
	GetParticles = 10;

}

void AMyEnemy::BeginPlay()
{
	Super::BeginPlay();
	PSC->Activate();
}

void AMyEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bGotHit == true)
	{
		GetParticles = PSC->GetNumActiveParticles();
		if (GetParticles == 0)
		{
			Destroy();
		}
	}
}

void AMyEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMyEnemy::Destroyed()
{
	Super::Destroyed();

	if (GetWorld())
	{
		AGruppe2_1GameModeBase* MyGameMode = Cast<AGruppe2_1GameModeBase>(GetWorld()->GetAuthGameMode());
		if (MyGameMode)
		{
			MyGameMode->IncrementNumberOfEnemiesKilled(EnemyID);
		}
	}
}

void AMyEnemy::GetDestroyed()
{
	bGotHit = true;
	PSC->Deactivate();
	SetActorEnableCollision(false);
}
