// Sjekk hvilke includes jeg faktisk bruker
#include "MyCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
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
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	//const float ForwardValue = GetInputAxisKeyValue(MoveForwardBinding);
	//const float RightValue = GetInputAxisKeyValue(MoveRightBinding);

	//Clamp movement
	//const FVector MoveDirection = FVector(ForwardValue, RightValue, 0.f).GetClampedToMaxSize(1.f);

	////Calculate movement
	//const FVector Movement = MoveDirection * MoveSpeed * DeltaTime;


	//if (Movement.SizeSquared() > 0.0f)
	//{
	//	const FRotator NewRotation = Movement.Rotation();
	//	FHitResult Hit(1.f);
	//	RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);

	//	if (Hit.IsValidBlockingHit())
	//	{
	//		const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
	//		const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
	//		RootComponent->MoveComponent(Deflection, NewRotation, true);
	//	}
	//}
}

void AMyCharacter::MoveForward(float Value) {
	if (Value != 0.f) {
	//	FVector Forward = GetActorForwardVector();
		FVector Forward = FVector(-1.f, 1.f, 0.f);
	//	AddMovementInput(CameraComponent->GetForwardVector)
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

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	//Set up key bindings
	PlayerInputComponent->BindAxis("MoveForward", this , &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::MyJump);
//	PlayerInputComponent->BindAxis(TurnBinding);

	//const FName AMyCharacter::MoveForwardBinding("MoveForward");
	//const FName AMyCharacter::MoveRightBinding("MoveRight");
	//const FName AMyCharacter::TurnBinding("Turn");
}

