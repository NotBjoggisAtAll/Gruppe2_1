// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyEnemy.h"
#include "Enemy_3.generated.h"

// Enemy 3 er "Moth"

UCLASS()
class GRUPPE2_1_API AEnemy_3 : public AMyEnemy
{
	GENERATED_BODY()
	
public:
	AEnemy_3();

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
