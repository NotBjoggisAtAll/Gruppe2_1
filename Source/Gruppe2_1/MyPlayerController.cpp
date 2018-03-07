// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "MyCharacter.h"

AMyPlayerController::AMyPlayerController(const FObjectInitializer & ObjectInitializer) : APlayerController()
{
}

void AMyPlayerController::BeginPlay() {
	Super::BeginPlay();
	bShowMouseCursor = true;
	Player = Cast<AMyCharacter>(GetCharacter());
}

void AMyPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	RotateToCursor();
}
void AMyPlayerController::RotateToCursor()
{
	if (Player != nullptr)
	{
		FVector WorldLocation;
		FVector WorldDirection;
		DeprojectMousePositionToWorld(WorldLocation, WorldDirection);
		auto Intersection = FMath::LinePlaneIntersection(WorldLocation, WorldLocation + (WorldDirection * 50000), Player->GetActorLocation(), FVector(0, 0, 1));
		auto NewYaw = UKismetMathLibrary::FindLookAtRotation(Player->GetActorLocation(), Intersection).Yaw;
		FRotator TargetRotation = FRotator(0.f, NewYaw, 0.f);
		Player->GetCapsuleComponent()->SetWorldRotation(TargetRotation);
	}
}

