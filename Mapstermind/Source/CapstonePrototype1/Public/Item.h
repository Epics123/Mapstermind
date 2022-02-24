// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	MASK		UMETA(DisplayName="Mask"),
	BASEBALL	UMETA(DisplayName="Baseball"),
	HOURGLASS	UMETA(DisplayName="Hourglass"),
	CLAMHAT		UMETA(DisplayName="Clam Hat"),
	CLAMEYES	UMETA(DisplayName="Clam Eyes")
};

UCLASS()
class CAPSTONEPROTOTYPE1_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemType itemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool canPickUp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
