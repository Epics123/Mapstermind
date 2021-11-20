// Fill out your copyright notice in the Description page of Project Settings.


#include "ControlButton.h"

// Sets default values
AControlButton::AControlButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CanActivate = true;
}

// Called when the game starts or when spawned
void AControlButton::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AControlButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AControlButton::InteractHand(ACharacter* Hand, bool isLeft)
{
	if (CanActivate)
	{
		ActivateButton(Hand, isLeft);
	}
}

