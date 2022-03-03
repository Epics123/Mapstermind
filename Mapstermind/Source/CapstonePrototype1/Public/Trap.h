// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Road.h"
#include "Trap.generated.h"

UCLASS()
class CAPSTONEPROTOTYPE1_API ATrap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrap();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsPlaced;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsJailCell;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsInWorld;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector OriginalLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector OriginalScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ARoad* Road;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ActivatePlacedTrap();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void RotateTrap();
};
