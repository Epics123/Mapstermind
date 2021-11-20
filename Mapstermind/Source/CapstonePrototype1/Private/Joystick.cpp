// Fill out your copyright notice in the Description page of Project Settings.


#include "Joystick.h"

AJoystick::AJoystick()
{
	MaxRollAngle = 30.0f;
	MaxPitchAngle = 30.0f;
}

void AJoystick::BeginPlay()
{
	Super::BeginPlay();

	OriginalLevelRot = Level->GetActorRotation();
}

void AJoystick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AJoystick::InteractHand(ACharacter* Hand, bool isLeft)
{
	
}

void AJoystick::RotateLevel(float xInput, float yInput)
{
	FRotator currentRot = Level->GetActorRotation();

	float newRoll = currentRot.Roll += xInput;
	float newPitch = currentRot.Pitch += yInput;

	if(newRoll <= -MaxRollAngle)
		newRoll = -MaxRollAngle;
	if(newRoll >= MaxRollAngle)
		newRoll = MaxRollAngle;
	if (newPitch <= -MaxPitchAngle)
		newPitch = -MaxPitchAngle;
	if (newPitch >= MaxPitchAngle)
		newPitch = MaxPitchAngle;

	currentRot.Roll = newRoll;
	currentRot.Pitch = newPitch;

	Level->SetActorRotation(currentRot);
}

void AJoystick::ResetLevelRotation()
{
	Level->SetActorRotation(OriginalLevelRot);
}
