// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Classes/Particles/ParticleSystemComponent.h"
#include "MyEnemy.generated.h"

UCLASS()
class GRUPPE2_1_API AMyEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	AMyEnemy();
	void GetDestroyed();

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void Destroyed() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(Category = Particles, EditAnywhere, BlueprintReadWrite)
	class UParticleSystemComponent* PSC;
	
	UPROPERTY(BlueprintReadOnly)
	bool bGotHit;
	
	int GetParticles;

	int EnemyID;
	
	float Strength;
};
