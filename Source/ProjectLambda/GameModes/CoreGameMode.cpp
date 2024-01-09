// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreGameMode.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ProjectLambda/Leaderboard/TimeLeaderboard.h"


ACoreGameMode::ACoreGameMode()
{

}

void ACoreGameMode::BeginPlay()
{
	Super::BeginPlay();

	//Initialise leader board manager
	LeaderboardManager = new TimeLeaderboard(LeaderboardFileName);
	
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
	//Stop the timer
	GetWorldTimerManager().ClearTimer(TimerHandle);

	//Store the timer
	//@@TODO Add flag to check if player won the game to store the timer,
	//@@TODO for testing i have left this so we can get dummy data into the file
	if (LeaderboardManager)
	{
		LeaderboardManager->SaveTimeToFile(PlayerTime);
		times = LeaderboardManager->GetTimeStrings();
	}
}

void ACoreGameMode::EndGame(bool PlayerWon)
{
	this->bPlayerWon = PlayerWon;

	EndTimer();
}
