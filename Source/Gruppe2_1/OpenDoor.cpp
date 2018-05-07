// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	bDoorOpen = false;
	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AGruppe2_1GameModeBase* GameMode = Cast<AGruppe2_1GameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode) {
		if (bDoorOpen == false) {

			if (GameMode->GetNextLevel() == true) {
					UE_LOG(LogTemp, Warning, TEXT("Opens door!"))
					bDoorOpen = true;
					OnOpenRequest.Broadcast();
			}
		}
	}

}