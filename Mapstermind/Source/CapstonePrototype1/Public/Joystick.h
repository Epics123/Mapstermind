// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Joystick.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONEPROTOTYPE1_API AJoystick : public AInteractable
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadWrite)
	bool CanActivate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Level")
	AActor* Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Rotation")
	float MaxRollAngle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Rotation")
	float MaxPitchAngle;

	FRotator OriginalLevelRot;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	AJoystick();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void InteractHand(ACharacter* Hand, bool isLeft) override;

	UFUNCTION(BlueprintImplementableEvent)
	void ActivateJoystick(ACharacter* Hand, bool isLeft);

	UFUNCTION(BlueprintCallable)
	void RotateLevel(float xInput, float yInput);

	UFUNCTION(BlueprintCallable)
	void ResetLevelRotation();
};
