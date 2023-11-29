// Copyright Epic Games, Inc. All Rights Reserved.


#include "ProjectLambdaGameModeBase.h"

#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetSystemLibrary.h"


// Map generation stuff
#include "MapGeneration/RoomManager.h"
#include "MapGeneration/Room.h"
#include "EngineUtils.h"

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



void AProjectLambdaGameModeBase::InitialiseMap(int mapHeight, int mapWidth)
{
	Map.SetNum(mapHeight);
	for (int i = 0; i < mapHeight; i++)
	{
		Map[i].column.SetNum(mapWidth);
		for (int j = 0; j < mapWidth; j++)
		{
			Map[i].column[j] = nullptr;
		}
	}
}

// Registers a room into the stored map array
void AProjectLambdaGameModeBase::RegisterRoom(ARoom* Room, int Horizontal, int Vertical)
{
	Map[Horizontal].column[Vertical] = Room;
}

ARoomManager* AProjectLambdaGameModeBase::GetMapManager()
{
	for (ARoomManager* FoundInstance : TActorRange<ARoomManager>(GetWorld()))
	{
		// Do something with the found instance
		if (FoundInstance)
		{
			// Found manager object
			return FoundInstance;
		}
	}

	// No manager found
	return nullptr;
	
}

ARoom* AProjectLambdaGameModeBase::GetRoomAt(int Horizontal, int Vertical)
{
	return Map[Horizontal].column[Vertical];
}
