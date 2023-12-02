// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ProjectLambdaGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTLAMBDA_API AProjectLambdaGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

#pragma region Properties
private:
	
	
	FTimerHandle TimerHandle;

public:

	//Stores time as text
	UPROPERTY(BlueprintReadOnly, Category="")
	FString TimerTxt = "";

	UPROPERTY(BlueprintReadOnly, Category = "")

	//Track how quickly the player finishes the game
	double PlayerTime = 0;

#pragma endregion

	
#pragma region Actions
	
private:

	////Track how quickly the player finishes the game
	//double PlayerTime = 0;

	//Starts timer when game starts
	void StartTimer();
	void IncrementTimer();

	//Starts timer when player finishes the game
	void EndTimer();

#pragma endregion


	
};
