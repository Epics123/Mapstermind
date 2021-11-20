// Fill out your copyright notice in the Description page of Project Settings.


#include "Health.h"

// Sets default values
UHealth::UHealth()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

}

void UHealth::initHealth(float startingHealth)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	mMaxHealth = startingHealth;
	mCurrentHealth = startingHealth;
}

float UHealth::getCurrentHealth()
{
	return mCurrentHealth;
}

float UHealth::getMaxHealth()
{
	return mMaxHealth;
}

void UHealth::lowerHealth(float lowerBy)
{
	mCurrentHealth -= lowerBy;
}