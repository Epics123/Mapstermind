// Fill out your copyright notice in the Description page of Project Settings.


#include "JailCellButton.h"

AJailCellButton::AJailCellButton()
{
	CanActivate = true;
}

void AJailCellButton::Interact(ACapstonePrototype1Character* Character)
{
	if (Character->IsEnemy && CanActivate)
		ActivateJail();
}
