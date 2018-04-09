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
	// Sets default values for this character's properties
	AMyEnemy();
	void GetDestroyed();


protected:
	UPROPERTY(Category = Particles, EditAnywhere, BlueprintReadWrite)
	class UParticleSystemComponent* PSC;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Destroyed() override;

	
	bool GotHit;
	int GetParticles;
	float Strength;
};
