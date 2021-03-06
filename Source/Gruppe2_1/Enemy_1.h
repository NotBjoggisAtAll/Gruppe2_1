// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyEnemy.h"
#include "Enemy_1.generated.h"

// Enemy 1 er "Spider"

UCLASS()
class GRUPPE2_1_API AEnemy_1 : public AMyEnemy
{
	GENERATED_BODY()

public:
	AEnemy_1();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
