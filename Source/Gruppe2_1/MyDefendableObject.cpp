// Fill out your copyright notice in the Description page of Project Settings.

#include "MyDefendableObject.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
AMyDefendableObject::AMyDefendableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	Collision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));

	RootComponent = Collision;
	StaticMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AMyDefendableObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyDefendableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

