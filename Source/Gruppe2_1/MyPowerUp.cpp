// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPowerUp.h"
#include "UObject/ConstructorHelpers.h"


// Sets default values
AMyPowerUp::AMyPowerUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("/Game/Meshes/Powerup.Powerup"));

	PowerUp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PowerUp"));

}

// Called when the game starts or when spawned
void AMyPowerUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float yRotation = 100.f * DeltaTime;
	FRotator Rotation = FRotator(0.f, yRotation, 0.f);
	
	AddActorLocalRotation(Rotation);

}

