// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePowerUp.h"

#include "ProjectLambda/GameModes/CoreGameMode.h"


// Sets default values
ABasePowerUp::ABasePowerUp()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Flag to ensure that the pick up isnt destroyed when timer finishes
	bPickUp = false;
}

// Called when the game starts or when spawned
void ABasePowerUp::BeginPlay()
{
	Super::BeginPlay();
	
}

bool ABasePowerUp::CheckCurrencyAmount()
{
	//Get currency
	int CurrentCurrency = CoreGameMode->Currency;
	
	//Check if the player has enough currency
	return CurrentCurrency >= Cost;
}

// Called every frame
void ABasePowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABasePowerUp::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

