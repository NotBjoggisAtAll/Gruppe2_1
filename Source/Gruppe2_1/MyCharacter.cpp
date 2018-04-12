// Sjekk hvilke includes jeg faktisk bruker
#include "MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "MyFireRateUp.h"

AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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

	GunOffset = FVector(100.f, 0.f, 0.f);
	FireRate = 1.f;
	bCanFire = true;
	bCanGetHurt = true;
	bFireRateOn = false;
}

void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMyCharacter::OnOverlapBegin);
}

void AMyCharacter::Tick(float DeltaTime)
{
	UWorld* World = GetWorld();
	Super::Tick(DeltaTime);

	if (bIsShooting == true)
	{
		Shooting();
	}
		FireRateRemaining = World->GetTimerManager().GetTimerElapsed(TimerHandle_ShotTimerExpired);
}

float AMyCharacter::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (bCanGetHurt || DamageAmount < 0)
	{
		UWorld* World = GetWorld();
		Health -= DamageAmount;
		bCanGetHurt = false;
		World->GetTimerManager().SetTimer(TimerHandle_ResetCanGetHurt, this, &AMyCharacter::ResetCanGetHurt, 2.f); //TODO Lag en variabel istedenfor hardkodet verdi.
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
			bFireRateOn = true;
			World->GetTimerManager().SetTimer(TimerHandle_ResetToNormalFireRate, this, &AMyCharacter::ResetToNormalFireRate, 2.f); //TODO Lag en variabel istedenfor hardkodet verdi.
			OtherActor->Destroy();
	}
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	//Set up key bindings
	PlayerInputComponent->BindAxis("MoveForward", this , &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AMyCharacter::StartShooting);
	PlayerInputComponent->BindAction("Shoot", IE_Released, this, &AMyCharacter::StopShooting);

}

void AMyCharacter::MoveForward(float Value)
{
	const UWorld* World = GetWorld();
	FVector SpawnLocation = GetActorLocation();
	if (Value != 0.f)
	{
		FVector Forward = FVector(-1.f, 1.f, 0.f);
		AddMovementInput(Forward, Value);
		// TODO FIX SOUND
		//UGameplayStatics::PlaySoundAtLocation(World, Walk, SpawnLocation);
	}
}

void AMyCharacter::MoveRight(float Value) {
	if (Value != 0.f) {
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

	UE_LOG(LogTemp, Warning, TEXT("YouCanGetHurt"))

}

void AMyCharacter::ResetToNormalFireRate()
{
	FireRate = 1.f;
	bFireRateOn = false;
}