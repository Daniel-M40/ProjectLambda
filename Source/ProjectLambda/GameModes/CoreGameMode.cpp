// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreGameMode.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetSystemLibrary.h"


void ACoreGameMode::BeginPlay()
{
	Super::BeginPlay();

	//Start timer when game starts
	StartTimer();
}

void ACoreGameMode::SpawnPickup(const FVector Location)
{
	UE_LOG(LogTemp, Warning, TEXT("Spawn Pickup at %s"), *Location.ToString());
}

void ACoreGameMode::StartTimer()
{
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ACoreGameMode::IncrementTimer, TimerRate, true);
}

void ACoreGameMode::IncrementTimer()
{
	//Get current game time in seconds, also effected when game is paused and slo-mo
	PlayerTime = UKismetSystemLibrary::GetGameTimeInSeconds(this);

	//Convert the time in seconds to string to display
	TimerTxt = UKismetStringLibrary::TimeSecondsToString(PlayerTime);
}

void ACoreGameMode::EndTimer()
{
	GetWorldTimerManager().ClearTimer(TimerHandle);
}
