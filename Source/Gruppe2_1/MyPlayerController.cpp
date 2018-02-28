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
		FHitResult CursorHit;
		bShowMouseCursor = true;
		GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel1), true, OUT CursorHit);
		auto NewYaw = UKismetMathLibrary::FindLookAtRotation(Player->GetActorLocation(), CursorHit.Location).Yaw;
		FRotator TargetRotation = FRotator(0.f, NewYaw, 0.f);
		Player->GetCapsuleComponent()->SetWorldRotation(TargetRotation);
	}
}

