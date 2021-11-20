// Fill out your copyright notice in the Description page of Project Settings.


#include "Hand.h"

// Sets default values
AHand::AHand()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HandMovementMultipiler = 6.0f;

	LGrabbing = false;
	RGrabbing = false;

	LPressed = false;
	RPressed = false;

	RPullingLever = false;
	LPullingLever = false;

	IsInverted = false;
	RHoldingItem = false;
	LHoldingItem = false;
	IsStunned = false;

	InteractDistance = 200.0f;
	HandHealth = CreateDefaultSubobject<UHealth>(TEXT("HandHealth"));
}

// Called when the game starts or when spawned
void AHand::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHand::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHand::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind Hand Movement
	PlayerInputComponent->BindAxis("MoveForward", this, &AHand::MoveLeftHandForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHand::MoveLeftHandRight);
	PlayerInputComponent->BindAxis("MoveRightHandForward", this, &AHand::MoveRightHandForward);
	PlayerInputComponent->BindAxis("MoveRightHandRight", this, &AHand::MoveRightHandRight);

	// Bind Hand Grab
	PlayerInputComponent->BindAxis("RHandGrab", this, &AHand::RHandGrab);
	PlayerInputComponent->BindAxis("LHandGrab", this, &AHand::LHandGrab);

	// Bind Hand Press Button
	PlayerInputComponent->BindAction("RHandPressButton", IE_Pressed, this, &AHand::RHandPress);
	PlayerInputComponent->BindAction("RHandPressButton", IE_Released, this, &AHand::RHandRelease);
	PlayerInputComponent->BindAction("LHandPressButton", IE_Pressed, this, &AHand::LHandPress);
	PlayerInputComponent->BindAction("LHandPressButton", IE_Released, this, &AHand::LHandRelease);
}

void AHand::MoveLeftHandForward(float Value)
{
	// Check if trigger has been pressed

	if (Value != 0 && !IsStunned)
	{
		if (!IsInverted)
		{
			if (!LGrabbing)
			{
				LeftHandPos.X += (100.0f * GetWorld()->GetDeltaSeconds()) * Value * HandMovementMultipiler;
				if(LeftHandPos.X > MaxHandPosX)
					LeftHandPos.X = MaxHandPosX;
				if(LeftHandPos.X < MinHandPosX)
					LeftHandPos.X = MinHandPosX;
			}
			// Check if left hand is grabbing something
			if (LGrabbing)
			{
				// Check if left hand is holding an item
				if (LHoldingItem)
				{
					// Move hand forward
					LeftHandPos.X += (100.0f * GetWorld()->GetDeltaSeconds()) * Value * HandMovementMultipiler;
					if (LeftHandPos.X > MaxHandPosX)
						LeftHandPos.X = MaxHandPosX;
					if (LeftHandPos.X < MinHandPosX)
						LeftHandPos.X = MinHandPosX;

					// Reset level rotation if grabbing the joystick
					if (LCurrentJoystick)
						LCurrentJoystick->ResetLevelRotation();
				}
				else
				{
					if (LCurrentJoystick)
					{
						LCurrentJoystick->RotateLevel(0.0f, -Value);
					}

					// Check if left hand is holding the joystick
					/*if (LCurrentJoystick)
						LCurrentJoystick->RotateLevel(0.0f, -Value);*/ //Rotate level


				}
			}
		}
		// Move hand normally
		else
		{
			if (!LGrabbing)
			{
				LeftHandPos.X -= (100.0f * GetWorld()->GetDeltaSeconds()) * Value * HandMovementMultipiler;
				if (LCurrentJoystick)
					LCurrentJoystick->ResetLevelRotation();
			}
			else
			{
				if (LCurrentJoystick)
					LCurrentJoystick->RotateLevel(0.0f, Value);
			}
			// Move hand forward
			LeftHandPos.X += (100.0f * GetWorld()->GetDeltaSeconds()) * Value * HandMovementMultipiler;

			// Reset level rotation if grabbing the joystick
			if(LCurrentJoystick)
				LCurrentJoystick->ResetLevelRotation();
		}
		
	}

	// Update the hand's position
	UpdateHandPositions();
}

void AHand::MoveLeftHandRight(float Value)
{
	// Check if trigger has been pressed
	if (Value != 0 && !IsStunned)
	{
		if (!IsInverted)
		{
			if (!LGrabbing)
			{
				LeftHandPos.Y += (100.0f * GetWorld()->GetDeltaSeconds()) * Value * HandMovementMultipiler;
				if(LeftHandPos.Y > MaxHandPosY)
					LeftHandPos.Y = MaxHandPosY;
				if(LeftHandPos.Y < MinHandPosY)
					LeftHandPos.Y = MinHandPosY;

				if (LCurrentJoystick)
					LCurrentJoystick->ResetLevelRotation();
			}
			else
			{
				if (LCurrentJoystick)
					LCurrentJoystick->RotateLevel(Value, 0.0f);
			}
			// Check if left hand is grabbing something
			if (LGrabbing)
			{
				// Check if left hand is holding an item
				if (LHoldingItem)
				{
					// Move hand right
					LeftHandPos.Y += (100.0f * GetWorld()->GetDeltaSeconds()) * Value * HandMovementMultipiler;
					if (LeftHandPos.Y > MaxHandPosY)
						LeftHandPos.Y = MaxHandPosY;
					if (LeftHandPos.Y < MinHandPosY)
						LeftHandPos.Y = MinHandPosY;

					// Reset level rotation if grabbing the joystick
					if (LCurrentJoystick)
						LCurrentJoystick->ResetLevelRotation();
				}
				else
				{
					// Check if left hand is holding the joystick
					//if (LCurrentJoystick)
						//LCurrentJoystick->RotateLevel(Value, 0.0f); // Rotate level
				}
			}
		}
		else
		{
			if (!LGrabbing)
			{
				LeftHandPos.Y -= Value * (100.0f * GetWorld()->GetDeltaSeconds()) * Value * HandMovementMultipiler;
				if (LCurrentJoystick)
					LCurrentJoystick->ResetLevelRotation();
			}
			else
			{
				if (LCurrentJoystick)
					LCurrentJoystick->RotateLevel(-Value, 0.0f);
			}
			// Move hand right
			LeftHandPos.Y += (100.0f * GetWorld()->GetDeltaSeconds()) * Value * HandMovementMultipiler;

			// Reset level rotation if grabbing the joystick
			if (LCurrentJoystick)
				LCurrentJoystick->ResetLevelRotation();
		}
	}

	// Update the hand's position
	UpdateHandPositions();
}

void AHand::MoveRightHandForward(float Value)
{
	if (Value != 0 && ! IsStunned)
	{
		if (!IsInverted)
		{
			if (!RGrabbing)
			{
				RightHandPos.X -= (100.0f * GetWorld()->GetDeltaSeconds()) * Value * HandMovementMultipiler;
				if (RightHandPos.X > MaxHandPosX)
					RightHandPos.X = MaxHandPosX;
				if (RightHandPos.X < MinHandPosX)
					RightHandPos.X = MinHandPosX;

				if (RCurrentJoystick)
					RCurrentJoystick->ResetLevelRotation();
			}
			else
			{
				if (RCurrentJoystick)
					RCurrentJoystick->RotateLevel(0.0f, Value);
			}
			if (RGrabbing)
			{

				if (RHoldingItem)
				{
					RightHandPos.X -= (100.0f * GetWorld()->GetDeltaSeconds()) * Value * HandMovementMultipiler;
					if (RightHandPos.X > MaxHandPosX)
						RightHandPos.X = MaxHandPosX;
					if (RightHandPos.X < MinHandPosX)
						RightHandPos.X = MinHandPosX;

					if (RCurrentJoystick)
						RCurrentJoystick->ResetLevelRotation();
				}
				else
				{
					//if (RCurrentJoystick)
						//RCurrentJoystick->RotateLevel(0.0f, Value);
				}
			}
		}
		else
		{
			if (!RGrabbing)
			{
				RightHandPos.X += (100.0f * GetWorld()->GetDeltaSeconds()) * Value * HandMovementMultipiler;

				if (RCurrentJoystick)
					RCurrentJoystick->ResetLevelRotation();
			}
			else
			{
				if (RCurrentJoystick)
					RCurrentJoystick->RotateLevel(0.0f, -Value);
			}
			RightHandPos.X -= (100.0f * GetWorld()->GetDeltaSeconds()) * Value * HandMovementMultipiler;
			if (RCurrentJoystick)
				RCurrentJoystick->ResetLevelRotation();
		}
	}

	UpdateHandPositions();
}

void AHand::MoveRightHandRight(float Value)
{
	if (Value != 0 && !IsStunned)
	{
		if (!IsInverted)
		{
			if (!RGrabbing)
			{
				RightHandPos.Y += (100.0f * GetWorld()->GetDeltaSeconds()) * Value * HandMovementMultipiler;
				if (RightHandPos.Y > MaxHandPosY)
					RightHandPos.Y = MaxHandPosY;
				if (RightHandPos.Y < MinHandPosY)
					RightHandPos.Y = MinHandPosY;
			}
		}

		if (RGrabbing)
		{
			if (RHoldingItem)
			{
				RightHandPos.Y += (100.0f * GetWorld()->GetDeltaSeconds()) * Value * HandMovementMultipiler;
				if (RightHandPos.Y > MaxHandPosY)
					RightHandPos.Y = MaxHandPosY;
				if (RightHandPos.Y < MinHandPosY)
					RightHandPos.Y = MinHandPosY;

				if (RCurrentJoystick)
					RCurrentJoystick->ResetLevelRotation();
			}
			else
			{
				if (RCurrentJoystick)
					RCurrentJoystick->RotateLevel(Value, 0.0f);
				//if (RCurrentJoystick)
					//RCurrentJoystick->RotateLevel(Value, 0.0f);
			}
		}
		else
		{
			if (!RGrabbing)
			{
				RightHandPos.Y -= (100.0f * GetWorld()->GetDeltaSeconds()) * Value * HandMovementMultipiler;

				if (RCurrentJoystick)
					RCurrentJoystick->ResetLevelRotation();
			}
			else
			{
				if (RCurrentJoystick)
					RCurrentJoystick->RotateLevel(-Value, 0.0f);
			}
			RightHandPos.Y += (100.0f * GetWorld()->GetDeltaSeconds()) * Value * HandMovementMultipiler;
			if (RCurrentJoystick)
				RCurrentJoystick->ResetLevelRotation();
		}
	}

	UpdateHandPositions();
}

void AHand::LHandGrab(float Value)
{
	if (Value != 0 && !IsStunned)
	{
		LGrabbing = true;

		GrabItem(true);

		if (LCurrentLever)
			LCurrentLever->InteractHand(this, true);
	}
	else
	{
		LGrabbing = false;

		if(LHoldingItem)
			ReleaseItem(true);
	}
}

void AHand::RHandGrab(float Value)
{
	if (Value != 0 && !IsStunned)
	{
		RGrabbing = true;

		GrabItem(false);

		if(RCurrentLever)
			RCurrentLever->InteractHand(this, false);
	}
	else
	{
		RGrabbing = false;

		if(RHoldingItem)
			ReleaseItem(false);
	}
}

void AHand::LHandPress()
{
	LPressed = true;

	PlayPressAnimation(true);

	if(LCurrentButton)
		LCurrentButton->InteractHand(this, true);
}

void AHand::LHandRelease()
{
	LPressed = false;
}

void AHand::RHandPress()
{
	RPressed = true;

	PlayPressAnimation(false);

	if (RCurrentButton)
		RCurrentButton->InteractHand(this, false);
}

void AHand::RHandRelease()
{
	RPressed = false;
}

FVector AHand::GetLeftHandPos()
{
	return LeftHandPos;
}

void AHand::SetLeftHandPos(FVector pos)
{
	LeftHandPos = pos;
}

FVector AHand::GetRightHandPos()
{
	return RightHandPos;
}

void AHand::SetRightHandPos(FVector pos)
{
	RightHandPos = pos;
}

