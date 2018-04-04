// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyEnemy.h"
#include "Enemy_2.generated.h"

/**
 * 
 */
UCLASS()
class GRUPPE2_1_API AEnemy_2 : public AMyEnemy
{
	GENERATED_BODY()

public:
	AEnemy_2();
	
protected:
	
	// Called when the game starts or when spawned
	void BeginPlay() override;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	
	
};
