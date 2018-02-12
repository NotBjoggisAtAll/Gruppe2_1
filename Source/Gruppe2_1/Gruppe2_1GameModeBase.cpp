// Fill out your copyright notice in the Description page of Project Settings.

#include "Gruppe2_1GameModeBase.h"
#include "MySpawnpoint.h"

AGruppe2_1GameModeBase::AGruppe2_1GameModeBase() {

	PrimaryActorTick.bCanEverTick = true;

	bCanSpawnEnemies = true;
	NumberOfEnemiesKilled = 0;

}

void AGruppe2_1GameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UE_LOG(LogTemp, Warning, TEXT("TEST"));
}

