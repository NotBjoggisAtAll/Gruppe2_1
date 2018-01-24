// Sjekk hvilke includes jeg faktisk bruker
#include "MyCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Projectile.h"

//const FName AMyCharacter::MoveForwardBinding("MoveForward");
//const FName AMyCharacter::MoveRightBinding("MoveRight");
//const FName AMyCharacter::TurnBinding("Turn");

// Sets default values
AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Camera boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->RelativeRotation = FRotator(-45.f, 130.f, 0.f);
	CameraBoom->bUsePawnControlRotation = false;

	// Create Camera
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;

	// Movement
	MoveSpeed = 1000.0f;
	// Weapon
	GunOffset = FVector(90.f, 0.f, 0.f);
	FireRate = 0.1f;
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

void AMyCharacter::Shoot()
{
//	if (bCanFire = true) {
		UWorld* const World = GetWorld();
		if (World) {
			FVector Location = GetActorLocation();
			World->SpawnActor<AProjectile>(BulletBlueprint, Location + GunOffset, GetActorRotation());
		}
	//	AProjectile* Bullet = World->SpawnActor<AProjectile>(GetActorLocation(), GetActorRotation());
	//}
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	//Set up key bindings
	PlayerInputComponent->BindAxis("MoveForward", this , &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::MyJump);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AMyCharacter::Shoot);
//	PlayerInputComponent->BindAxis(TurnBinding);

	//const FName AMyCharacter::MoveForwardBinding("MoveForward");
	//const FName AMyCharacter::MoveRightBinding("MoveRight");
	//const FName AMyCharacter::TurnBinding("Turn");
}

