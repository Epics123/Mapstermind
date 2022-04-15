// Copyright Epic Games, Inc. All Rights Reserved.

#include "CapstonePrototype1Character.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interactable.h"

//////////////////////////////////////////////////////////////////////////
// ACapstonePrototype1Character

ACapstonePrototype1Character::ACapstonePrototype1Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	InteractDistance = 100.0f;
	IsEnemy = false;
	PullingLever = false;
	CanMove = true;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void ACapstonePrototype1Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ACapstonePrototype1Character::Interact);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACapstonePrototype1Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACapstonePrototype1Character::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ACapstonePrototype1Character::TurnAtRate);
	//PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ACapstonePrototype1Character::LookUpAtRate);
	//PlayerInputComponent->BindAxis("PullLever", this, &ACapstonePrototype1Character::PullLever);
}


void ACapstonePrototype1Character::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ACapstonePrototype1Character::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	//AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

bool ACapstonePrototype1Character::PullLever(float Value)
{
	if ((Controller != nullptr) && (Value < -0.5f))
	{
		return true;
	}
	return false;
}

void ACapstonePrototype1Character::Interact()
{
	FHitResult outHit;
	FVector start = GetActorLocation();
	FVector end = start + GetActorForwardVector() * InteractDistance; 

	if (GetWorld()->LineTraceSingleByChannel(outHit, start, end, ECC_Visibility))
	{
		AInteractable* hitObj = Cast<AInteractable>(outHit.Actor);
		if (hitObj)
		{
			hitObj->Interact(this);
		}
	}
}

void ACapstonePrototype1Character::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f) && CanMove)
	{
		if (invertMovement)
			Value *= -1;
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ACapstonePrototype1Character::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) && CanMove)
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
