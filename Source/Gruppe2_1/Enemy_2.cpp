// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy_2.h"
#include "Kismet/GameplayStatics.h"
#include "MyCharacter.h"
#include "Components/CapsuleComponent.h"

AEnemy_2::AEnemy_2()
{
	Strength = 1.f;
}

void AEnemy_2::BeginPlay()
{
	Super::BeginPlay();
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemy_2::OnOverlapBegin);
}

void AEnemy_2::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	auto Player = Cast<AMyCharacter>(OtherActor);
	if (Player)
	{
		FHitResult HitResult;
		UGameplayStatics::ApplyPointDamage(OtherActor, Strength, GetActorForwardVector(), HitResult, GetController(), this, UDamageType::StaticClass());
		UE_LOG(LogTemp, Warning, TEXT("Enemy2HitYou!"))
	}
}


