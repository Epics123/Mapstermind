// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "SpringButton.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROTOTYPE1_API ASpringButton : public AInteractable
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
	bool CanActivate;
	
public:

	ASpringButton();

	virtual void Interact(ACapstonePrototype1Character* Character) override;

	UFUNCTION(BlueprintImplementableEvent)
	void ActivateSprings();
};
