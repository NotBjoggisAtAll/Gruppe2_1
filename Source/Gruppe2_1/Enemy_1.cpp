// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy_1.h"
#include "Kismet/GameplayStatics.h"
#include "MyCharacter.h"
#include "Components/CapsuleComponent.h"

AEnemy_1::AEnemy_1()
{
	Strength = 2.f;
}

void AEnemy_1::BeginPlay()
{
	Super::BeginPlay();
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemy_1::OnOverlapBegin);
}

void AEnemy_1::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	auto Player = Cast<AMyCharacter>(OtherActor);
	if (Player)
	{
		FHitResult HitResult;
		UGameplayStatics::ApplyPointDamage(OtherActor, Strength, GetActorForwardVector(), HitResult, GetController(), this, UDamageType::StaticClass());
		UE_LOG(LogTemp, Warning, TEXT("Enemy1HitYou!"))
	}
}


