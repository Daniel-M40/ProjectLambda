// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CoreGameMode.generated.h"

/**
 * 
 */
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
	UPROPERTY(BlueprintReadOnly, Category = "")
	double PlayerTime = 0;

#pragma endregion

	
#pragma region Actions

public:
	virtual void BeginPlay() override;
	
private:
	//Starts timer when game starts
	void StartTimer();
	
	void IncrementTimer();

	//Starts timer when player finishes the game
	void EndTimer();

	
#pragma endregion
};
