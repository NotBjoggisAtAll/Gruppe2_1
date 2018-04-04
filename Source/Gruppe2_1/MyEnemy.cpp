// Fill out your copyright notice in the Description page of Project Settings.

#include "MyEnemy.h"
#include "Gruppe2_1GameModeBase.h"
#include "Projectile.h"
#include "MyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"


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
//	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMyEnemy::OnOverlapBegin);
	
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

//void AMyEnemy::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
//{
//	auto Player = Cast<AMyCharacter>(OtherActor);
//	if (Player)
//	{
//		FHitResult HitResult;
//		UGameplayStatics::ApplyPointDamage(OtherActor, Strength, GetActorForwardVector(), HitResult, GetController(), this, UDamageType::StaticClass());
//	}
//}

