// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPowerUp.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

AMyPowerUp::AMyPowerUp()
{
	PrimaryActorTick.bCanEverTick = true;

	PowerUp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PowerUp"));
	OverlapCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	RootComponent = OverlapCollision;
	PowerUp->SetupAttachment(RootComponent);
}
void AMyPowerUp::BeginPlay()
{
	Super::BeginPlay();

	FVector NewLocation = FVector(GetActorLocation().X, GetActorLocation().Y, 110.f);
	SetActorLocation(NewLocation);
}

void AMyPowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float yRotation = 100.f * DeltaTime;
	FRotator Rotation = FRotator(0.f, yRotation, 0.f);
	AddActorLocalRotation(Rotation);
}

USphereComponent * AMyPowerUp::GetSphere()
{
	return OverlapCollision;
}
