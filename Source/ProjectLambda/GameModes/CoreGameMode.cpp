// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ProjectLambda/Leaderboard/TimeLeaderboard.h"
#include "ProjectLambda/PickUp/BasePickUp.h"


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

	//Get length of pick up array
	PickUpArrLength = PickUpArr.Num();
}

void ACoreGameMode::IncreaseCurrency(int value)
{
	Currency += value;
}

void ACoreGameMode::DecreaseCurrency(int value)
{
	Currency -= value;
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
		GetLeaderboardTimes();
	}
}

void ACoreGameMode::EndGame(bool PlayerWon)
{
	this->bPlayerWon = PlayerWon;

	this->bGameOver = true;
	
	EndTimer();

	if (PlayerWon)
	{
		UGameplayStatics::OpenLevel(this, FName(WinScreenLevel));
	}
	else
	{
		UGameplayStatics::OpenLevel(this, FName(GameOverLevel));
	}
}


void ACoreGameMode::GetLeaderboardTimes()
{
	if (LeaderboardManager)
	{
		timeArr = LeaderboardManager->GetTimerValues();
	}
}

void ACoreGameMode::SpawnPickUp(const FVector Location, const FRotator Rotation)
{
	//Check length of pick up arr
	if (PickUpArrLength <= 0)
	{
		return;
	}
	
	//Randomly spawn Pick up if the value is 1
	const int spawnPowerUp = FMath::RandRange(0, PickUpSpawnRate);

	if (spawnPowerUp)
	{
		//Randomly pick Pick up in array
		const int index = FMath::RandRange(0, PickUpArrLength - 1);
		
		//Spawn Pick up in location
		if (PickUpArr[index])
		{
			GetWorld()->SpawnActor<ABasePickUp>(PickUpArr[index], Location, Rotation);
		}
		
	}
}
