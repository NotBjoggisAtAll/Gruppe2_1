// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "MyTriggerVolume.generated.h"

UCLASS()
class GRUPPE2_1_API AMyTriggerVolume : public ATriggerVolume
{
	GENERATED_BODY()

public:
		AMyTriggerVolume();

protected:
	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);
};