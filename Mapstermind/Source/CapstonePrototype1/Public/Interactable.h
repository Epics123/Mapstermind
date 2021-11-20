// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CapstonePrototype1/CapstonePrototype1Character.h"
//#include "Hand.h"
#include "Interactable.generated.h"

UCLASS()
class CAPSTONEPROTOTYPE1_API AInteractable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	virtual void Interact(ACapstonePrototype1Character* Character) PURE_VIRTUAL(AInteractable::Interact(), );

	virtual void InteractHand(ACharacter* Hand, bool isLeft) PURE_VIRTUAL(AInteractable::InteractHand(), );
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
