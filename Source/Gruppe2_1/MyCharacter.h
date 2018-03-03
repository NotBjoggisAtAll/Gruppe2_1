// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

class AProjectile;
class USoundBase;

UCLASS()
class GRUPPE2_1_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AProjectile> Projectile_BP;

public:
	// Sets default values for this character's properties
	AMyCharacter();

	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		USoundBase* FireShot;

	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		USoundBase* JumpSound;

	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		USoundBase* LandSound;

	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		USoundBase* Walk;



	/** Offset from the ships location to spawn projectiles */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		FVector GunOffset;

	/* How fast the weapon will fire */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float FireRate;

	/* Checks if the weapon can fire*/
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		bool bCanFire;

	/* Checks if the weapon can fire*/
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		bool bIsWalking;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		int Health;

	void TakeDamage();


	void MoveForward(float Value);
	void MoveRight(float Value);
	
	
	//FTimerHandle TimerHandle_DodgeForwardExpired;
	//void DodgeForwardExpired();
	//bool DodgeForward;

	bool hasLanded;
	
	float TakeDamageTimer;
	bool CanTakeDamage;

	void MyJump();
	virtual void Landed(const FHitResult& Hit) override;


	bool isShooting;

	void StartShooting();
	void Shooting();
	void StopShooting();

	void ShotTimerExpired();

	/** Handle for efficient management of ShotTimerExpired timer */
	FTimerHandle TimerHandle_ShotTimerExpired;
public:	

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
