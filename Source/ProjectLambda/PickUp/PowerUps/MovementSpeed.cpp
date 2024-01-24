// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementSpeed.h"

#include "ProjectLambda/GameModes/CoreGameMode.h"
#include "ProjectLambda/Player/PlayerCharacter.h"


// Sets default values
AMovementSpeed::AMovementSpeed()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMovementSpeed::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMovementSpeed::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMovementSpeed::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Check if we have enough currency
	if (CheckCurrencyAmount())
	{
		//Subtract currency from player
		CoreGameMode->DecreaseCurrency(Cost);

		//Increase health
		PlayerCharacter->MovementSpeed += MovementSpeedIncrease;

		//@@TODO Play sounds effects here
		
		Destroy();
	}
}

