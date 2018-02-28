// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GRUPPE2_1_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

		AMyPlayerController(const FObjectInitializer & ObjectInitializer);

		virtual void BeginPlay() override;
		virtual void Tick(float DeltaTime) override;

		void RotateToCursor();
	
	class AMyCharacter* Player;
};
