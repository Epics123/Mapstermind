// Fill out your copyright notice in the Description page of Project Settings.


#include "Lever.h"

ALever::ALever()
{
	CanActivate = true;
}

void ALever::Interact(ACapstonePrototype1Character* Character)
{
	if (CanActivate)
	{
		ActivateLever(Character);
		Character->PullingLever = true;
	}
}

void ALever::InteractHand(ACharacter* Hand, bool isLeft)
{
	if (CanActivate)
	{
		HandActivateLever(Hand, isLeft);
	}
}
