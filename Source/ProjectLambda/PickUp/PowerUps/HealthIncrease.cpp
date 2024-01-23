// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthIncrease.h"

#include "ProjectLambda/Components/HealthComponent.h"
#include "ProjectLambda/GameModes/CoreGameMode.h"
#include "ProjectLambda/Player/PlayerCharacter.h"


// Sets default values
AHealthIncrease::AHealthIncrease()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AHealthIncrease::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHealthIncrease::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHealthIncrease::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Check if we have enough currency
	if (CheckCurrencyAmount())
	{
		//Subtract currency from player
		CoreGameMode->DecreaseCurrency(Cost);

		//Increase health
		PlayerCharacter->IncreaseMaxHealth(MaxHealthIncrease);
	}
}

