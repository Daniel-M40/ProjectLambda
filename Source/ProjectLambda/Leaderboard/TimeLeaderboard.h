// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class PROJECTLAMBDA_API TimeLeaderboard
{
private:
	TArray<double> TimeValues;

	const int TimeValLimit = 10;

	FString FileName;

	
public:
	TimeLeaderboard(FString FileName);
	~TimeLeaderboard();
	
	void SaveTimeToFile(double TimeValue);
	
	void LoadTimeFromFile();
	
	TArray<double> GetTimerValues();
};
