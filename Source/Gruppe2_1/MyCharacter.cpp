// Sjekk hvilke includes jeg faktisk bruker
#include "MyCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Projectile.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "MyEnemy.h"
#include "MyHealthUp.h"
#include "MyFireRateUp.h"

// Sets default values
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
	CameraBoom->TargetArmLength = 1000.f;
	CameraBoom->RelativeRotation = FRotator(-45.f, 130.f, 0.f);
	CameraBoom->bUsePawnControlRotation = false;
	CameraBoom->bInheritYaw = false;

	// Create Camera
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;

	Health = 10.f;
	DamageTimer = 0;

	// Sets default values to variables
	GunOffset = FVector(100.f, 0.f, 0.f);
	FireRate = 1.f;
	bCanFire = true;
	hasLanded = true;
	bIsWalking = false;
	bCanGetHurt = true;
	FireRateOn = false;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMyCharacter::OnOverlapBegin);
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	UWorld* World = GetWorld();
	Super::Tick(DeltaTime);
	if (isShooting == true) {
		Shooting();
	}
		FireRateRemaining = World->GetTimerManager().GetTimerElapsed(TimerHandle_ShotTimerExpired);
	if (bCanGetHurt == false)
	{
		DamageTimer += DeltaTime;

		if (DamageTimer >= 2)
		{
			bCanGetHurt = true;
			DamageTimer = 0;
			UE_LOG(LogTemp, Warning, TEXT("YouCanGetHurt"))
		}
	}
	if (FireRateOn == true)
	{
		FireRateOnTimer += DeltaTime;
		if (FireRateOnTimer > 2)
		{
			FireRate = 1;
			FireRateOn = false;
		}
	}
}

// Runs when you use press the movement buttons
void AMyCharacter::MoveForward(float Value) {
	const UWorld* World = GetWorld();
	FVector SpawnLocation = GetActorLocation();
	if (Value != 0.f) {
		bIsWalking = true;
		FVector Forward = FVector(-1.f, 1.f, 0.f);
		AddMovementInput(Forward, Value);
		// TODO FIX SOUND
		//UGameplayStatics::PlaySoundAtLocation(World, Walk, SpawnLocation);
	}
	bIsWalking = false;
	/*if (DodgeForward == true) {
		UE_LOG(LogTemp, Warning, TEXT("DODGING!!"))
	}
	World->GetTimerManager().SetTimer(TimerHandle_DodgeForwardExpired, this, &AMyCharacter::DodgeForwardExpired, 1.f);
	DodgeForward = false; */
}

//void AMyCharacter::DodgeForwardExpired() {
//	DodgeForward = false;
//}

// Runs when you use press the movement buttons
void AMyCharacter::MoveRight(float Value) {
	if (Value != 0.f) {
		bIsWalking = true;
		FVector Right = FVector(-1.f, -1.f, 0.f);
		AddMovementInput(Right, Value);
	}
	bIsWalking = false;
}

// Runs when you press the Jump button
void AMyCharacter::MyJump() {
	if (hasLanded == true) {
	UWorld* const World = GetWorld();
	FVector SpawnLocation = GetActorLocation();
	Jump();
	UGameplayStatics::PlaySoundAtLocation(World, JumpSound, SpawnLocation);
	hasLanded = false;
	}
}

void AMyCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	UWorld* World = GetWorld();
	UGameplayStatics::PlaySoundAtLocation(World, LandSound, GetActorLocation());
	hasLanded = true;
}
// Runs when you press the Shoot button
void AMyCharacter::StartShooting()
{
	isShooting = true;
}

// Runs while you hold the Shoot button
void AMyCharacter::Shooting()
{
	if (bCanFire == true) {
		const FVector FireDirection = GetActorForwardVector();
		const FRotator FireRotation = FireDirection.Rotation();
		const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset); //TODO Spørre om hvorfor dette ikke fungerer

		UWorld* const World = GetWorld();
		if (World != NULL) {
			World->SpawnActor<AProjectile>(Projectile_BP, SpawnLocation, FireRotation);
			UGameplayStatics::PlaySoundAtLocation(World, FireShot, GetActorLocation());
		}
		bCanFire = false;
		World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AMyCharacter::ShotTimerExpired, FireRate);
	}
}
// Runs when you release the Shoot button
void AMyCharacter::StopShooting()
{
	isShooting = false;
}

void AMyCharacter::ShotTimerExpired()
{
	bCanFire = true;
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	//Set up key bindings
	PlayerInputComponent->BindAxis("MoveForward", this , &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::MyJump);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AMyCharacter::StartShooting);
	PlayerInputComponent->BindAction("Shoot", IE_Released, this, &AMyCharacter::StopShooting);

}

float AMyCharacter::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (bCanGetHurt || DamageAmount < 0)
	{
	Health -= DamageAmount;
	bCanGetHurt = false;
	if (Health > 10)
	{
		Health = 10.f;
	}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("OnCoolDown!"))
	}
	if (Health == 0)
	{
		Destroy();
	}
	return DamageAmount;
}

void AMyCharacter::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	auto FireRateUp = Cast<AMyFireRateUp>(OtherActor);
	if (FireRateUp)
	{
			FireRateOnTimer = 0.f;
			FireRate = 0.1f;
			FireRateOn = true;
			OtherActor->Destroy();
	}
}
