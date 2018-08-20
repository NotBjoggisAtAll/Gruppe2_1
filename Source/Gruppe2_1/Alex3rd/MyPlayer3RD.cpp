// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayer3RD.h"


// Sets default values
AMyPlayer3RD::AMyPlayer3RD()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyPlayer3RD::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPlayer3RD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPlayer3RD::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

