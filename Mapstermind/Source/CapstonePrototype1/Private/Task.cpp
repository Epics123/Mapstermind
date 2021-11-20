// Fill out your copyright notice in the Description page of Project Settings.


#include "Task.h"

// Sets default values
ATask::ATask()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Completed = false;
}

// Called when the game starts or when spawned
void ATask::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATask::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

