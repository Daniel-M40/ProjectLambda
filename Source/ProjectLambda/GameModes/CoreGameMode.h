// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CoreGameMode.generated.h"


UCLASS()
class PROJECTLAMBDA_API ACoreGameMode : public AGameModeBase
{
	GENERATED_BODY()

#pragma region Properties
private:
	FTimerHandle TimerHandle;

	UPROPERTY(EditAnywhere, Category="Timer")
	float TimerRate = 0.01f;
	
public:

	//Stores time as text
	UPROPERTY(BlueprintReadOnly, Category="Timer")
	FString TimerTxt = "";

	//Track how quickly the player finishes the game
	UPROPERTY(BlueprintReadOnly, Category="Timer")
	double PlayerTime = 0;

	UPROPERTY(BlueprintReadOnly)
	bool bPlayerWon = false;
	
#pragma endregion

	
#pragma region Actions

public:
	virtual void BeginPlay() override;
	
	void SpawnPickup(const FVector Location);


private:
	//Starts timer when game starts
	void StartTimer();
	
	void IncrementTimer();

	//Starts timer when player finishes the game
	void EndTimer();

public:
	
	/**
	 * Ends the game
	 * @param bPlayerWon Flag to show whether the player has won the game or not
	 */
	void EndGame(bool bPlayerWon);
	
	
#pragma endregion
};
