// Fill out your copyright notice in the Description page of Project Settings.

#include "MovementSpeedPowerUp.h"
#include "ProjectLambda/GameModes/CoreGameMode.h"
#include "ProjectLambda/Player/PlayerCharacter.h"

void AMovementSpeedPowerUp::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (CheckCurrencyAmount()) // check if there's enough currency
	{
		CoreGameMode->DecreaseCurrency(Cost); // decrease currency based on price 

		PlayerCharacter->MovementSpeed += IncreaseMovementSpeed; // increase player speed

		Destroy(); // destroy power up
	}
}
