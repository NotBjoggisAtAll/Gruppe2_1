// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "MyPowerUp.generated.h"


UCLASS()
class GRUPPE2_1_API AMyPowerUp : public AActor
{
	GENERATED_BODY()

private:
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* PowerUp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
		USphereComponent* OverlapCollision;

		
	
public:	
	// Sets default values for this actor's properties
	AMyPowerUp();

	USphereComponent* GetSphere();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
