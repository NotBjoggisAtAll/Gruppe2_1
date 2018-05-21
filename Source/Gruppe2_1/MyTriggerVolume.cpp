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

void AMyTriggerVolume::OnOverlapBegin(AActor * OverlappedActor, AActor * OtherActor)
{
	if (OtherActor && (OtherActor != this))
	{
		auto Player = Cast<AMyCharacter>(OtherActor);
		AGruppe2_1GameModeBase* GameMode = Cast<AGruppe2_1GameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
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