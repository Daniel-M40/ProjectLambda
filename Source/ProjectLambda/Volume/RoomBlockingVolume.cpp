// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomBlockingVolume.h"

#include "Components/BoxComponent.h"


// Sets default values
ARoomBlockingVolume::ARoomBlockingVolume()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create box component default components
	OverlapVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("BlockingVolume"));

	//Set the box component attachment to the root component.
	OverlapVolume->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ARoomBlockingVolume::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoomBlockingVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

