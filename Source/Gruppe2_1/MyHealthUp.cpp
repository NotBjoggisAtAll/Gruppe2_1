// Fill out your copyright notice in the Description page of Project Settings.

#include "MyHealthUp.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "MyCharacter.h"

AMyHealthUp::AMyHealthUp()
{
	HealAmount = -2.f;
}

void AMyHealthUp::BeginPlay()
{
	Super::BeginPlay();
	GetSphere()->OnComponentBeginOverlap.AddDynamic(this, &AMyHealthUp::OnOverlapBegin);
}

void AMyHealthUp::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
	{
		auto Player = Cast<AMyCharacter>(OtherActor);
		if(Player)
		{	
			FHitResult HitResult;
			UGameplayStatics::ApplyPointDamage(OtherActor, HealAmount, GetActorForwardVector(), HitResult, UGameplayStatics::GetPlayerController(GetWorld(), 0), this, UDamageType::StaticClass());
			Destroy();
		}
	}