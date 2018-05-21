// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"

UOpenDoor::UOpenDoor()
{
	PrimaryComponentTick.bCanEverTick = true;

	bDoorOpen = false;
}

void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AGruppe2_1GameModeBase* GameMode = Cast<AGruppe2_1GameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		if (bDoorOpen == false)
		{
			if (GameMode->GetNextLevel() == true)
			{
				UE_LOG(LogTemp, Warning, TEXT("Opens door!"))
					bDoorOpen = true;
				OnOpenRequest.Broadcast();
			}
		}
	}
}