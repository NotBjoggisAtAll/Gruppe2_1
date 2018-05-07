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

	AMyCharacter();

	//Audio 

	UPROPERTY(Category = "Audio", EditAnywhere, BlueprintReadWrite)
		USoundBase* FireShot;

	UPROPERTY(Category = "Audio", EditAnywhere, BlueprintReadWrite)
		USoundBase* Walk;

	//Getters

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Health")
		float GetHealth() const { return Health; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Health")
		bool GetCanGetHurt() const { return bCanGetHurt; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "FireRate")
		bool GetFireRateOn() const { return bFireRateOn; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "FireRate")
		float GetFireRateRemaining() const { return FireRateRemaining; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "FireRate")
		bool GetCanFire() const { return bCanFire; }

	//Setter
	UFUNCTION(BlueprintCallable, Category = "Health")
		void SetCanGetHurt(bool bInput) { bCanGetHurt = bInput; }

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//Input functions
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);
	void MoveRight(float Value);

	void StartShooting();
	void StopShooting();

	void Shooting();

	//Timerhandles and function related to them
	FTimerHandle TimerHandle_ShotTimerExpired;	
	FTimerHandle TimerHandle_ResetCanGetHurt;
	FTimerHandle TimerHandle_ResetToNormalFireRate;
	
	void ShotTimerExpired();
	void ResetCanGetHurt();
	void ResetToNormalFireRate();

	//Variables

	bool bCanGetHurt;
	bool bIsShooting;
	bool bCanFire;
	bool bFireRateOn;

	float Health;
	float FireRate;
	float FireRateRemaining;
	
	FVector GunOffset;
};