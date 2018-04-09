// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyPowerUp.h"
#include "MyFireRateUp.generated.h"

UCLASS()
class GRUPPE2_1_API AMyFireRateUp : public AMyPowerUp
{
	GENERATED_BODY()
	
public:
	AMyFireRateUp();
protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};