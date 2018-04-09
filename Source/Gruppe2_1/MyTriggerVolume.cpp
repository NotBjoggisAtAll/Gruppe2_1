// Fill out your copyright notice in the Description page of Project Settings.

#include "MyTriggerVolume.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "MyCharacter.h"

AMyTriggerVolume::AMyTriggerVolume()
{
	OnActorBeginOverlap.AddDynamic(this, &AMyTriggerVolume::OnOverlapBegin);
}

void AMyTriggerVolume::BeginPlay()
{
	Super::BeginPlay();
	
	//Brukes kun til debugging, for å vise hvor triggerboxen er
	DrawDebugBox(GetWorld(), GetActorLocation(), GetActorScale() * 100, FColor::Cyan, true, -1, 0, 5);
}

void AMyTriggerVolume::OnOverlapBegin(AActor * OverlappedActor, AActor * OtherActor)
{
	if (OtherActor && (OtherActor != this)) {
		auto Player = Cast<AMyCharacter>(OtherActor);
		if (Player)
		{
			UE_LOG(LogTemp, Warning, TEXT("Overlap Begin!"));
			UGameplayStatics::OpenLevel(GetWorld(), TEXT("/Game/Maps/Level_2"), TRAVEL_Absolute);
		}
	}
}