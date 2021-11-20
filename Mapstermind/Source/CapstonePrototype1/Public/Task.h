// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Task.generated.h"

UCLASS()
class CAPSTONEPROTOTYPE1_API ATask : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATask();

	UPROPERTY(BlueprintReadWrite)
	bool Completed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void CompleteTask();
};
