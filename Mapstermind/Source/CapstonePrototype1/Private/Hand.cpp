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

/*
* MoveLeftHandForward
* Moves the left hand forward/backwards based on input value
*	Param Value: Normalized (0-1) input value from the player
*/
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
				}
			}
		}
		
	}

	// Update the hand's position
	UpdateHandPositions();
}

/*
* MoveLeftHandRight
* Moves the left hand right/left based on input value
*	Param Value: Normalized (0-1) input value from the player
*/
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
				}
			}
		}
	}

	// Update the hand's position
	UpdateHandPositions();
}

/*
* MoveRightHandForward
* Moves the right hand forward/backwards based on input value
*	Param Value: Normalized (0-1) input value from the player
*/
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
				}
			}
		}
	}

	UpdateHandPositions();
}

/*
* MoveRightHandRight
* Moves the right hand right/left based on input value
*	Param Value: Normalized (0-1) input value from the player
*/
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
			}

		}
	}

	UpdateHandPositions();
}

/*
* LHandGrab
* Grab an item when left trigger is held
*	Param Value: Normalized (0-1) input value from the player
*/
void AHand::LHandGrab(float Value)
{
	// Check if trigger is held
	if (Value != 0 && !IsStunned)
	{
		// Grab item
		LGrabbing = true;
		GrabItem(true);
	}
	else
	{	
		// Release grabbed item
		LGrabbing = false;
		if(LHoldingItem)
			ReleaseItem(true);
	}
}

/*
* RHandGrab
* Grab an item when right trigger is held
*	Param Value: Normalized (0-1) input value from the player
*/
void AHand::RHandGrab(float Value)
{
	// Check if trigger is held
	if (Value != 0 && !IsStunned)
	{
		// Grab item
		RGrabbing = true;
		GrabItem(false);
	}
	else
	{
		// Release grabbed item
		RGrabbing = false;
		if(RHoldingItem)
			ReleaseItem(false);
	}
}

/*
* LHandPress
* Initiate button press when player presses the left bumper
*/
void AHand::LHandPress()
{
	LPressed = true;

	// Check if we are over a button
	if (LCurrentButton)
	{
		PlayPressAnimation(true);
		LCurrentButton->InteractHand(this, true); // If we are, interact w/ the button
	}
	else if (LCurrentLever)
	{
		PlayPullAnimation(true);
		LCurrentLever->InteractHand(this, true);
	}
}

/*
* LHandRelease
* Stop button press when player releases the left bumper
*/
void AHand::LHandRelease()
{
	LPressed = false;
}

/*
* RHandPress
* Initiate button press when player presses the right bumper
*/
void AHand::RHandPress()
{
	RPressed = true;

	// Check if we are over a button
	if (RCurrentButton)
	{
		PlayPressAnimation(false);
		RCurrentButton->InteractHand(this, false); // If we are, interact w/ the button
	}
	else if (RCurrentLever)
	{
		PlayPullAnimation(false);
		RCurrentLever->InteractHand(this, true);
	}
		
}

/*
* RHandRelease
* Stop button press when player releases the right bumper
*/
void AHand::RHandRelease()
{
	RPressed = false;
}

/*
* GetLeftHandPos
* Get the current position of the left hand relative to the hand BP
*	Return: relative left hand position
*/
FVector AHand::GetLeftHandPos()
{
	return LeftHandPos;
}

/*
* SetLeftHandPos
* Set the current position of the left hand relative to the hand BP
*	Param pos: relative left hand position
*/
void AHand::SetLeftHandPos(FVector pos)
{
	LeftHandPos = pos;
}

/*
* GetRightHandPos
* Get the current position of the right hand relative to the hand BP
*	Return: relative right hand position
*/
FVector AHand::GetRightHandPos()
{
	return RightHandPos;
}

/*
* SetRightHandPos
* Set the current position of the right hand relative to the hand BP
*	Param pos: relative right hand position
*/
void AHand::SetRightHandPos(FVector pos)
{
	RightHandPos = pos;
}

void AHand::SetMaxHandPosX(float max)
{
	MaxHandPosX = max;
}

void AHand::SetMinHandPosX(float min)
{
	MinHandPosX = min;
}

void AHand::SetMaxHandPosY(float max)
{
	MaxHandPosY = max;
}

void AHand::SetMinHandPosY(float min)
{
	MinHandPosY = min;
}

