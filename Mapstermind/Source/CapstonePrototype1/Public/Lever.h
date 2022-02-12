// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Lever.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROTOTYPE1_API ALever : public AInteractable
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(BlueprintReadWrite)
	bool CanActivate;

public:

	ALever();

	// Player interaction
	virtual void Interact(ACapstonePrototype1Character* Character) override;
	virtual void InteractHand(ACharacter* Hand, bool isLeft) override;

	// Lever Activation
	UFUNCTION(BlueprintImplementableEvent)
	void ActivateLever(ACapstonePrototype1Character* Character);
	UFUNCTION(BlueprintImplementableEvent)
	void HandActivateLever(ACharacter* Hand, bool isLeft);
	
	UFUNCTION(BlueprintImplementableEvent)
	void Activate();
	UFUNCTION(BlueprintImplementableEvent)
	void Reset();
};
