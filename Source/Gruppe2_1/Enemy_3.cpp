// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy_3.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "MyCharacter.h"

AEnemy_3::AEnemy_3()
{
	Strength = 2.f;
}

void AEnemy_3::BeginPlay()
{
	Super::BeginPlay();
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemy_3::OnOverlapBegin);
}

void AEnemy_3::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	auto Player = Cast<AMyCharacter>(OtherActor);
	if (Player)
	{
		FHitResult HitResult;
		UGameplayStatics::ApplyPointDamage(OtherActor, Strength, GetActorForwardVector(), HitResult, GetController(), this, UDamageType::StaticClass());
	}
}


