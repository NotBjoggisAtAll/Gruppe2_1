// Fill out your copyright notice in the Description page of Project Settings.

#include "MyTriggerVolume.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "MyCharacter.h"
#include "Gruppe2_1GameModeBase.h"

AMyTriggerVolume::AMyTriggerVolume()
{
	OnActorBeginOverlap.AddDynamic(this, &AMyTriggerVolume::OnOverlapBegin);
}

void AMyTriggerVolume::BeginPlay()
{
	Super::BeginPlay();
	
	//TODO Lage en anne type effekt for å vise hvor triggerboksen er. (Lys, Partikler)??
	//Brukes kun til debugging, for å vise hvor triggerboxen er
	DrawDebugBox(GetWorld(), GetActorLocation(), GetActorScale() * 100, FColor::Cyan, true, -1, 0, 5);
}

void AMyTriggerVolume::OnOverlapBegin(AActor * OverlappedActor, AActor * OtherActor)
{
	if (OtherActor && (OtherActor != this)) {
		auto Player = Cast<AMyCharacter>(OtherActor);
		AGruppe2_1GameModeBase* GameMode = Cast<AGruppe2_1GameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode) {
			if (Player)
			{
				if (GameMode->GetNextLevel() == true)
				{
					UGameplayStatics::OpenLevel(GetWorld(), TEXT("/Game/Maps/testLevel02"), TRAVEL_Absolute);
				}
			}
		}
	}
}