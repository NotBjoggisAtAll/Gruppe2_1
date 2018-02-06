// Sjekk hvilke includes jeg faktisk bruker
#include "MyCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "Projectile.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

//const FName AMyCharacter::MoveForwardBinding("MoveForward");
//const FName AMyCharacter::MoveRightBinding("MoveRight");
//const FName AMyCharacter::TurnBinding("Turn");

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

	GunOffset = FVector(10.f, 0.f, 0.f);
	FireRate = 0.2f;
	bCanFire = true;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	if (isShooting == true) {
		if (bCanFire == true) {
			const FRotator FireRotation = FRotator(1.f, 0.f, 0.f);

			const FVector SpawnLocation = this->GetActorForwardVector() + GunOffset; //TODO Spørre om hvorfor dette ikke fungerer

			UWorld* const World = GetWorld();
			if (World != NULL) {
				World->SpawnActor<AProjectile>(Projectile_BP, SpawnLocation, FireRotation);
			}
			bCanFire = false;
			World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AMyCharacter::ShotTimerExpired, FireRate);
		}
	}
}

void AMyCharacter::MoveForward(float Value) {
	if (Value != 0.f) {
		FVector Forward = FVector(-1.f, 1.f, 0.f);
		AddMovementInput(Forward, Value);
	}
}

void AMyCharacter::MoveRight(float Value) {
	if (Value != 0.f) {
		FVector Right = FVector(-1.f, -1.f, 0.f);
		AddMovementInput(Right, Value);
	}
}

void AMyCharacter::MyJump() {
	Jump();
}

void AMyCharacter::StartShooting()
{
	isShooting = true;
	if (isShooting == true) {


		UE_LOG(LogTemp, Warning, TEXT("Shooting!"));
	}
}

void AMyCharacter::StopShooting()
{
	isShooting = false;
	UE_LOG(LogTemp, Warning, TEXT("Stopped shooting!"));
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
//	PlayerInputComponent->BindAxis(TurnBinding);

	//const FName AMyCharacter::MoveForwardBinding("MoveForward");
	//const FName AMyCharacter::MoveRightBinding("MoveRight");
	//const FName AMyCharacter::TurnBinding("Turn");
}

