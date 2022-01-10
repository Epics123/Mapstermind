// Fill out your copyright notice in the Description page of Project Settings.


#include "Lever.h"

ALever::ALever()
{
	CanActivate = true;
}

/*
* Interact
* Initiate lever interaction with a pieceling
*	Param Character: Character to interact with
*/
void ALever::Interact(ACapstonePrototype1Character* Character)
{
	// Check if lever can be activated
	if (CanActivate)
	{
		// Activate the lever
		ActivateLever(Character);
		Character->PullingLever = true;
	}
}

/*
* InteractHand
* Initiate lever interaction with a hand
*	Param Hand: Hand to interact with
*	Param isLeft: right or left hand
*/
void ALever::InteractHand(ACharacter* Hand, bool isLeft)
{
	// Check if lever can be activated
	if (CanActivate)
	{
		// Activate the lever
		HandActivateLever(Hand, isLeft);
	}
}
