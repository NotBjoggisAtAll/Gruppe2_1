// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class UStaticMeshComponent;
class AMyHealthUp;
class AMyFireRateUp;

UCLASS()
class GRUPPE2_1_API AProjectile : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		UProjectileMovementComponent* ProjectileMovement;

public:
	AProjectile();
	void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AMyHealthUp> Health_BP;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AMyFireRateUp> FireRate_BP;

	UPROPERTY(BlueprintReadOnly)
		FVector EnemyDeath;

	UPROPERTY(BlueprintReadOnly)
		bool EnemyHit = false;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	FORCEINLINE UStaticMeshComponent* GetProjectileMesh() const { return ProjectileMesh; }

	FORCEINLINE UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

private:
	float Speed;
};
