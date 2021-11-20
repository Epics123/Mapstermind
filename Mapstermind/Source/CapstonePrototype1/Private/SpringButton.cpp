// Fill out your copyright notice in the Description page of Project Settings.


#include "SpringButton.h"

ASpringButton::ASpringButton()
{
	CanActivate = true;
}

void ASpringButton::Interact(ACapstonePrototype1Character* Character)
{
	if(Character->IsEnemy && CanActivate)
		ActivateSprings();
}
