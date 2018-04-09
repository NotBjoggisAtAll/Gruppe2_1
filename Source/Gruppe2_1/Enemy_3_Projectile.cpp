// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy_3_Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "MyCharacter.h"

// Sets default values
AEnemy_3_Projectile::AEnemy_3_Projectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EnemyProjectileComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	RootComponent = EnemyProjectileComponent;

	Strength = 2.f;
}

// Called when the game starts or when spawned
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

// Called every frame
void AEnemy_3_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}