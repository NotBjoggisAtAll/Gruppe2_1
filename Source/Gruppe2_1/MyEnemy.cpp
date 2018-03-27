// Fill out your copyright notice in the Description page of Project Settings.

#include "MyEnemy.h"
#include "Gruppe2_1GameModeBase.h"
#include "Projectile.h"
#include "MyCharacter.h"
#include "Components/CapsuleComponent.h"


// Sets default values
AMyEnemy::AMyEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



}

// Called when the game starts or when spawned
void AMyEnemy::BeginPlay()
{
	Super::BeginPlay();
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AMyEnemy::OnHit);
	
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

void AMyEnemy::OnHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	auto Player = Cast<AMyCharacter>(OtherActor);
	if (Player)
	{
		//OtherActor->Destroy();
		UE_LOG(LogTemp, Warning, TEXT("DODGING!!"))
	}
}

