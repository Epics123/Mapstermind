// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "JailCellButton.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROTOTYPE1_API AJailCellButton : public AInteractable
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadWrite)
	bool CanActivate;

public:

	AJailCellButton();

	virtual void Interact(ACapstonePrototype1Character* Character) override;

	UFUNCTION(BlueprintImplementableEvent)
	void ActivateJail();
};
