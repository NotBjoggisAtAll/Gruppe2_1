// Fill out your copyright notice in the Description page of Project Settings.

#include "MyHealthUp.h"
#include "Kismet/GameplayStatics.h"
#include "MyCharacter.h"
#include "Components/SphereComponent.h"



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
	UE_LOG(LogTemp, Warning, TEXT("Health Overlapping"))
//		auto Player = Cast<AMyCharacter>(OtherActor);
		if (OtherActor->IsA(AMyCharacter::StaticClass()))
		{
			UE_LOG(LogTemp, Warning, TEXT("Found player"))
			FHitResult HitResult;
			UGameplayStatics::ApplyPointDamage(OtherActor, HealAmount, GetActorForwardVector(), HitResult, UGameplayStatics::GetPlayerController(GetWorld(), 0), this, UDamageType::StaticClass());
		}
	}
