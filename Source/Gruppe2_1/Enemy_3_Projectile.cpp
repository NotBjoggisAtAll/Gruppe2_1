// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy_3_Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "MyCharacter.h"

AEnemy_3_Projectile::AEnemy_3_Projectile()
{
	PrimaryActorTick.bCanEverTick = true;

	EnemyProjectileComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	RootComponent = EnemyProjectileComponent;

	Strength = 2.f;
}

void AEnemy_3_Projectile::BeginPlay()
{
	Super::BeginPlay();
	EnemyProjectileComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemy_3_Projectile::OnOverlapBegin);
}

void AEnemy_3_Projectile::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	auto Player = Cast<AMyCharacter>(OtherActor);
	if (Player)
	{
		FHitResult HitResult;
		UGameplayStatics::ApplyPointDamage(OtherActor, Strength, GetActorForwardVector(), HitResult, UGameplayStatics::GetPlayerController(GetWorld(), 0), this, UDamageType::StaticClass());
		Destroy();
	}
}