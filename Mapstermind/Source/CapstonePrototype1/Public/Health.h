// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Health.generated.h"

UCLASS()
class CAPSTONEPROTOTYPE1_API UHealth : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	UHealth();

	UFUNCTION(BlueprintCallable)
	void initHealth(float startingHealth);

	float getCurrentHealth();
	float getMaxHealth();

	void lowerHealth(float lowerBy = 1.0f);

private:
	float mMaxHealth;
	float mCurrentHealth;

};
