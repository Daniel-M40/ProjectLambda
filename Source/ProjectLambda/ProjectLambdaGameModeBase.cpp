// Copyright Epic Games, Inc. All Rights Reserved.


#include "ProjectLambdaGameModeBase.h"

#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetSystemLibrary.h"


void AProjectLambdaGameModeBase::StartTimer()
{
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AProjectLambdaGameModeBase::IncrementTimer, 1.f, true);
}

void AProjectLambdaGameModeBase::IncrementTimer()
{
	//Get current game time in seconds, also effected when game is paused and slo-mo
	PlayerTime = UKismetSystemLibrary::GetGameTimeInSeconds(this);

	//Convert the time in seconds to string to display
	TimerTxt = UKismetStringLibrary::TimeSecondsToString(PlayerTime);
}
