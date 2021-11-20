// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "ControlButton.generated.h"

UCLASS()
class CAPSTONEPROTOTYPE1_API AControlButton : public AInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AControlButton();

	UPROPERTY(BlueprintReadWrite)
	bool CanActivate;

	UPROPERTY(BlueprintReadWrite)
	bool Hovered;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void InteractHand(ACharacter* Hand, bool isLeft) override;

	UFUNCTION(BlueprintImplementableEvent)
	void ActivateButton(ACharacter* Hand, bool isLeft);

};
