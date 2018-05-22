// Sjekk hvilke includes jeg faktisk bruker
#include "MyCharacter.h"
#include "MyPlayerController.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Engine/Engine.h"
#include "TimerManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "MyFireRateUp.h"

AMyCharacter::AMyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Camera boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->RelativeRotation = FRotator(-45.f, 130.f, 0.f);
	CameraBoom->bUsePawnControlRotation = false;
	CameraBoom->bInheritYaw = false;

	// Create Camera
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;

	// Sets default values to variables
	Health = 10.f;
	FireRate = 1.f;
	FireRateDuration = 2.f;
	CanGetHurtAgainTimer = 2.f;

	GunOffset = FVector(100.f, 0.f, 0.f);
	bCanFire = true;
	bCanGetHurt = true;
	bFireRatePickedUp = false;
	bFireRateOn = false;
}

void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMyCharacter::OnOverlapBegin);
}

void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsShooting == true)
	{
		Shooting();
	}
	FireRateRemaining = GetWorld()->GetTimerManager().GetTimerElapsed(TimerHandle_ShotTimerExpired);
}

float AMyCharacter::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (bCanGetHurt || DamageAmount < 0)
	{
		UWorld* World = GetWorld();
		Health -= DamageAmount;
		if (DamageAmount > 0)
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), GetHurtSound, GetActorLocation());
		}
		bCanGetHurt = false;
		World->GetTimerManager().SetTimer(TimerHandle_ResetCanGetHurt, this, &AMyCharacter::ResetCanGetHurt, CanGetHurtAgainTimer);
		if (Health > 10)
		{
			Health = 10.f;
		}
	}
	return DamageAmount;
}

void AMyCharacter::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	auto FireRateUp = Cast<AMyFireRateUp>(OtherActor);
	if (FireRateUp)
	{
		UWorld* World = GetWorld();
		FireRate = 0.1f;
		bFireRatePickedUp = true;
		float PitchSound = FMath::FRandRange(0.8f, 1.2f);
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireRatePickupSound, GetActorLocation(), 1.f, PitchSound);
		OtherActor->Destroy();
	}
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AMyCharacter::StartShooting);
	PlayerInputComponent->BindAction("Shoot", IE_Released, this, &AMyCharacter::StopShooting);

}

void AMyCharacter::MoveForward(float Value)
{
	if (Value != 0.f && Health > 0)
	{
		FVector Forward = FVector(-1.f, 1.f, 0.f);
		AddMovementInput(Forward, Value);
	}
}

void AMyCharacter::MoveRight(float Value) {
	if (Value != 0.f && Health > 0) {
		FVector Right = FVector(-1.f, -1.f, 0.f);
		AddMovementInput(Right, Value);
	}
}

// Runs when you press the Shoot button
void AMyCharacter::StartShooting()
{
	bIsShooting = true;
}

// Runs when you release the Shoot button
void AMyCharacter::StopShooting()
{
	bIsShooting = false;
}

// Runs while you hold the Shoot button
void AMyCharacter::Shooting()
{
	if (bCanFire == true)
	{
		const FVector FireDirection = GetActorForwardVector();
		const FRotator FireRotation = FireDirection.Rotation();
		const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			World->SpawnActor<AProjectile>(Projectile_BP, SpawnLocation, FireRotation);
			UGameplayStatics::PlaySoundAtLocation(World, FireShot, GetActorLocation());
		}
		bCanFire = false;
		if (bFireRatePickedUp == true) {
			bFireRatePickedUp = false;
			bFireRateOn = true;
			World->GetTimerManager().SetTimer(TimerHandle_ResetToNormalFireRate, this, &AMyCharacter::ResetToNormalFireRate, FireRateDuration);
		}
		World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AMyCharacter::ShotTimerExpired, FireRate);
	}
}

void AMyCharacter::ShotTimerExpired()
{
	bCanFire = true;
}

void AMyCharacter::ResetCanGetHurt()
{
	bCanGetHurt = true;
}

void AMyCharacter::ResetToNormalFireRate()
{
	FireRate = 1.f;
	bFireRateOn = false;
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireRateDropSound, GetActorLocation());
}