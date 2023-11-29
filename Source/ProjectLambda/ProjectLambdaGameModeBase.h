// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ProjectLambdaGameModeBase.generated.h"

struct FRoomMapRow;
class ARoom;

/**
 * 
 */
UCLASS()
class PROJECTLAMBDA_API AProjectLambdaGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

#pragma region Properties
private:
	//Track how quickly the player finishes the game
	double PlayerTime = 0;
	
	FTimerHandle TimerHandle;

public:
	//Stores time as text
	UPROPERTY(BlueprintReadOnly, Category="")
	FString TimerTxt = "";
#pragma endregion

	
#pragma region Actions
	
private:
	//Starts timer when game starts
	void StartTimer();

	void IncrementTimer();

	//Starts timer when player finishes the game
	void EndTimer();

#pragma endregion



#pragma region Map Generation
public:
	void InitialiseMap(int mapHeight, int mapWidth);
	void RegisterRoom(ARoom* Room, int Horizontal, int Vertical);
	class ARoomManager* GetMapManager();
	ARoom* GetRoomAt(int Horizontal, int Vertical);

private:
	UPROPERTY(VisibleAnywhere)
		TArray<FRoomMapRow> Map;
#pragma endregion
	
};
