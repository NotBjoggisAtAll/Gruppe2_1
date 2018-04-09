// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/StaticMesh.h"
#include "Math/UnrealMathUtility.h"
#include "MyEnemy.h"
#include "MyHealthUp.h"
#include "MyFireRateUp.h"

// Sets default values
AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	Speed = 750.f;

	// Static reference to the mesh to use for the projectile
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("/Game/Meshes/Player/Projectile_Mesh.Projectile_Mesh"));

	// Create mesh component for the projectile sphere
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh0"));
	ProjectileMesh->SetStaticMesh(ProjectileMeshAsset.Object);
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->BodyInstance.SetCollisionProfileName("Projectile");
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);		// set up a notification for when this component hits something
	RootComponent = ProjectileMesh;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement0"));
	ProjectileMovement->UpdatedComponent = ProjectileMesh;
	ProjectileMovement->InitialSpeed = Speed;
	ProjectileMovement->MaxSpeed = Speed;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.f; // No gravity
						 
	InitialLifeSpan = 3.0f; // Die after 3 seconds by default
}
void AProjectile::Tick(float DeltaTime)
{
	float xRotation = 250.f * DeltaTime;
	FRotator ProjectileRotation = FRotator(0.f, 0.f, xRotation);
	AddActorLocalRotation(ProjectileRotation);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		auto Enemy = Cast<AMyEnemy>(OtherActor);
		if (Enemy) {
			EnemyDeath = OtherActor->GetActorLocation();
			EnemyHit = true;
			Enemy->Destroy();
			int RandomNumber = FMath::RandRange(1, 10);
                        UE_LOG(LogTemp, Warning, TEXT("My int is: %d"), RandomNumber)
			if(RandomNumber > 7)
			{
				if (RandomNumber == 10)
				{
					GetWorld()->SpawnActor<AMyFireRateUp>(FireRate_BP, EnemyDeath, FRotator(0));
				}
				else
				{
					GetWorld()->SpawnActor<AMyHealthUp>(Health_BP, EnemyDeath, FRotator(0));
				}
			}
		}
	}
	Destroy();
}