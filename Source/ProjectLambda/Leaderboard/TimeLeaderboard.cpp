// Fill out your copyright notice in the Description page of Project Settings.

#include "TimeLeaderboard.h"
#include "HAL/FileManager.h"
#include "Misc/FileHelper.h"
#include "Kismet/KismetStringLibrary.h"
#include "Math/UnitConversion.h"


TimeLeaderboard::TimeLeaderboard(FString FileName)
{
	this->FileName = FileName;
}

TimeLeaderboard::~TimeLeaderboard()
{
}

void TimeLeaderboard::SaveTimeToFile(double TimeValue)
{
	LoadTimeFromFile();
	
	// Get the path for the saved file
	FString SaveDirectory = FPaths::ProjectSavedDir();
	FString SavePath = FPaths::Combine(SaveDirectory, FileName);

	// Check if the directory exists, and if not, create it
	IFileManager::Get().MakeDirectory(*SaveDirectory, true);

	// Create and open the archive for writing
	FArchive* Ar = IFileManager::Get().CreateFileWriter(*SavePath);

	if (Ar)
	{
		// Add the current time value to the array
		TimeValues.Add(TimeValue);

		// Sort the array in ascending order
		Algo::Sort(TimeValues);

		// Truncate the array to keep only the last 10 values
		if (TimeValues.Num() > 10)
		{
			TimeValues.RemoveAt(0, TimeValues.Num() - 10);
		}

		// Serialize the sorted and truncated time values to the archive
		for (double Time : TimeValues)
		{
			*Ar << Time;
		}

		// Close the archive
		delete Ar;
	}
	else
	{
		// Handle the case where the file could not be created
		UE_LOG(LogTemp, Warning, TEXT("Failed to create or write to file: %s"), *SavePath);
	}
}

void TimeLeaderboard::LoadTimeFromFile()
{
	// Get the path for the saved file
	FString SaveDirectory = FPaths::ProjectSavedDir();
	FString SavePath = FPaths::Combine(SaveDirectory, FileName);

	// Check if the file exists before attempting to read
	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*SavePath))
	{
		// Create and open the archive for reading
		FArchive* Ar = IFileManager::Get().CreateFileReader(*SavePath);

		if (Ar)
		{
			// Deserialize the time values from the archive
			TimeValues.Empty();
			while (!Ar->AtEnd())
			{
				double Time;
				*Ar << Time;
				TimeValues.Add(Time);
			}

			// Close the archive
			delete Ar;
		}
	}
	else
	{
		// Handle the case where the file doesn't exist
		UE_LOG(LogTemp, Warning, TEXT("File does not exist: %s"), *SavePath);
	}
}

TArray<double> TimeLeaderboard::GetTimerValues()
{
	LoadTimeFromFile();
	
	return TimeValues;
}
