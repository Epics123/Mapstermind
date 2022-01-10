// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Lever.h"
#include "Health.h"
#include "ControlButton.h"
#include "Joystick.h"
#include "Trap.h"

#include "Hand.generated.h"

UCLASS()
class CAPSTONEPROTOTYPE1_API AHand : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHand();

	// Default hand positions (relative to hand BP)
	UPROPERTY(BlueprintReadWrite)
	FVector LeftHandPos = FVector(-20.0f, -190.0f, 0.0f);
	UPROPERTY(BlueprintReadWrite)
	FVector RightHandPos = FVector(-20.0f, 170.0f, 0.0f);

	// Movement
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float HandMovementMultipiler = 8.0f;

	// Hand State Booleans
	UPROPERTY(BlueprintReadWrite)
	bool LGrabbing;
	UPROPERTY(BlueprintReadWrite)
	bool RGrabbing;
	UPROPERTY(BlueprintReadOnly)
	bool RPressed;
	UPROPERTY(BlueprintReadWrite)
	bool LPressed;
	UPROPERTY(BlueprintReadWrite)
	bool RPullingLever;
	UPROPERTY(BlueprintReadWrite)
	bool LPullingLever;
	UPROPERTY(BlueprintReadWrite)
	bool LHoldingItem;
	UPROPERTY(BlueprintReadWrite)
	bool RHoldingItem;
	UPROPERTY(BlueprintReadWrite)
	bool IsInverted;
	UPROPERTY(BlueprintReadWrite)
	bool IsStunned;

	// Hand Constraints
	UPROPERTY(BlueprintReadWrite)
	float InteractDistance;
	UPROPERTY(BlueprintReadWrite)
	float MinHandPosX = -300.0f;
	UPROPERTY(BlueprintReadWrite)
	float MaxHandPosX = 6000.0f;
	UPROPERTY(BlueprintReadWrite)
	float MinHandPosY = -4600.0f;
	UPROPERTY(BlueprintReadWrite)
	float MaxHandPosY = 4600.0f;

	// Interactable Refs
	UPROPERTY(BlueprintReadWrite)
	ALever* LCurrentLever;
	UPROPERTY(BlueprintReadWrite)
	ALever* RCurrentLever;
	UPROPERTY(BlueprintReadWrite)
	AControlButton* LCurrentButton;
	UPROPERTY(BlueprintReadWrite)
	AControlButton* RCurrentButton;
	UPROPERTY(BlueprintReadWrite)
	AJoystick* LCurrentJoystick;
	UPROPERTY(BlueprintReadWrite)
	AJoystick* RCurrentJoystick;
	UPROPERTY(BlueprintReadWrite)
	ATrap* LCurrentItem;
	UPROPERTY(BlueprintReadWrite)
	ATrap* RCurrentItem;

	UPROPERTY(BlueprintReadWrite)
	UHealth* HandHealth;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Hand Movement
	void MoveLeftHandForward(float Value);
	void MoveLeftHandRight(float Value);
	void MoveRightHandForward(float Value);
	void MoveRightHandRight(float Value);

	// Hand Interaction
	void LHandGrab(float Value);
	void RHandGrab(float Value);
	void LHandPress();
	void LHandRelease();
	void RHandPress();
	void RHandRelease();

	// Blueprint Hand Interaction
	UFUNCTION(BlueprintImplementableEvent)
	void GrabItem(bool isLeft);
	UFUNCTION(BlueprintImplementableEvent)
	void ReleaseItem(bool isLeft);

	// Hand Positions
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateHandPositions();
	UFUNCTION(BlueprintCallable)
	FVector GetLeftHandPos();
	UFUNCTION(BlueprintCallable)
	void SetLeftHandPos(FVector pos);
	UFUNCTION(BlueprintCallable)
	FVector GetRightHandPos();
	UFUNCTION(BlueprintCallable)
	void SetRightHandPos(FVector pos);

	// Animation Control
	UFUNCTION(BlueprintImplementableEvent)
	void PlayPressAnimation(bool isLeft);

};
